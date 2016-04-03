using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class ColourConverter : Form
    {
        private double m_blendValue = 0.0f;
        private List<Button> m_blending = new List<Button>();
        private Random m_random = new Random(0);

        class RGB
        {
            public double Red = 0.0f;
            public double Green = 0.0f;
            public double Blue = 0.0f;
        };

        class HSV
        {
            public double Hue = 0.0f;
            public double Saturation = 0.0f;
            public double Value = 0.0f;
        };

        /// <summary>
        /// Constructur
        /// </summary>
        public ColourConverter()
        {
            InitializeComponent();

            colorDialog1.Color = Color.FromArgb(255, 128, 64);
            colorDialog2.Color = Color.FromArgb(0, 128, 255);
            button1.BackColor = colorDialog1.Color;
            button2.BackColor = colorDialog2.Color;

            m_blending.Add(b1);
            m_blending.Add(b2);
            m_blending.Add(b3);
            m_blending.Add(b4);
            m_blending.Add(b5);
            m_blending.Add(b6);
            m_blending.Add(b7);
            m_blending.Add(b8);
            m_blending.Add(b9);
            m_blending.Add(b10);
            m_blending.Add(b11);

            SetBlendValue();
            SetMiddleColour();
        }

        /// <summary>
        /// On Button 1 click show colour dialog
        /// </summary>
        private void button1_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                button1.BackColor = colorDialog1.Color;
                SetMiddleColour();
            }
        }

        /// <summary>
        /// On Button 2 click show colour dialog
        /// </summary>
        private void button2_Click(object sender, EventArgs e)
        {
            if (colorDialog2.ShowDialog() == DialogResult.OK)
            {
                button2.BackColor = colorDialog2.Color;
                SetMiddleColour();
            }
        }

        /// <summary>
        /// On Track bar value change
        /// </summary>
        private void trackBar1_ValueChanged(object sender, EventArgs e)
        {
            SetBlendValue();
            SetMiddleColour();
        }

        /// <summary>
        /// Converting RGB-HSV: http://www.poynton.com/PDFs/coloureq.pdf p15
        /// Where rgb is [0,1]
        /// </summary>
        private HSV ConvertColour(RGB rgb)
        {
            HSV hsv = new HSV();

            double min = Math.Min(Math.Min(rgb.Red, rgb.Blue), rgb.Green);
            double max = Math.Max(Math.Max(rgb.Red, rgb.Blue), rgb.Green);
            hsv.Saturation = max == 0.0f ? 0.0f : (max - min) / max;
            hsv.Value = max;

            double red = (max - rgb.Red) / (max - min);
            double green = (max - rgb.Green) / (max - min);
            double blue = (max - rgb.Blue) / (max - min);

            if (hsv.Saturation != 0)
            {
                if (rgb.Red == max && rgb.Green == min)
                {
                    hsv.Hue = 5.0f + blue;
                }
                else if (rgb.Red == max && rgb.Green != min)
                {
                    hsv.Hue = 1.0f - green;
                }
                else if (rgb.Green == max && rgb.Blue == min)
                {
                    hsv.Hue = 1.0f + red;
                }
                else if (rgb.Green == max && rgb.Blue != min)
                {
                    hsv.Hue = 3.0f - blue;
                }
                else if (rgb.Red == max || rgb.Red == min)
                {
                    hsv.Hue = 3.0f + green;
                }
                else
                {
                    hsv.Hue = 5.0f - red;
                }
            }

            hsv.Hue *= 60.0f;
            return hsv;
        }

        /// <summary>
        /// Converting HSV-RGB: http://www.poynton.com/PDFs/coloureq.pdf p15
        /// Where h is [0,360] and sv is [0,1]
        /// </summary>
        private RGB ConvertColour(HSV hsv)
        {
            RGB rgb = new RGB();

            double hex = hsv.Hue / 60.0f;
            int primary = (int)Math.Floor(hex);
            double secondary = hex - primary;
            double a = (1.0f - hsv.Saturation) * hsv.Value;
            double b = (1.0f - (hsv.Saturation * secondary)) * hsv.Value;
            double c = (1.0f - (hsv.Saturation * (1.0f - secondary))) * hsv.Value;

            switch(primary)
            {
            case 0:
                rgb.Red = hsv.Value;
                rgb.Green = c;
                rgb.Blue = a;
                break;
            case 1:
                rgb.Red = b;
                rgb.Green = hsv.Value;
                rgb.Blue = a;
                break;
            case 2:
                rgb.Red = a;
                rgb.Green = hsv.Value;
                rgb.Blue = c;
                break;
            case 3:
                rgb.Red = a;
                rgb.Green = b;
                rgb.Blue = hsv.Value;
                break;
            case 4:
                rgb.Red = c;
                rgb.Green = a;
                rgb.Blue = hsv.Value;
                break;
            case 5:
                rgb.Red = hsv.Value;
                rgb.Green = a;
                rgb.Blue = b;
                break;
            case 6:
                rgb.Red = hsv.Value;
                rgb.Green = c;
                rgb.Blue = a;
                break;
            }

            return rgb;
        }

        /// <summary>
        /// Colour Blending: http://www.stuartdenman.com/improved-color-blending/
        /// Where blend value is [0-1]
        /// </summary>
        private HSV BlendColour(HSV one, HSV two, double blendvalue)
        {
            HSV blend = new HSV();

            double invBlendValue = 1.0f - blendvalue;
            blend.Saturation = (one.Saturation * invBlendValue) + (two.Saturation * blendvalue);
            blend.Value = (one.Value * invBlendValue) + (two.Value * blendvalue);

            double hue1 = one.Hue;
            double hue2 = two.Hue;
            double difference = hue2 - hue1;

            if (hue1 > hue2)
            {
                hue2 = one.Hue;
                hue1 = two.Hue;

                blendvalue = invBlendValue;
                difference = -difference;
            }

            if(difference > 180)
            {
                hue1 += 360.0f;
                blend.Hue = ((int)(hue1 + (blendvalue * (hue2 - hue1)))) % 360;
            }
            else
            {
                blend.Hue = hue1 + (blendvalue * difference);
            }

            return blend;
        }

        /// <summary>
        /// Updates and sets the middle button colour
        /// </summary>
        private void SetMiddleColour()
        {
            Func<RGB, HSV, string> CreateColourText = (RGB rgb, HSV hsv) =>
            {
                return "R: " + rgb.Red.ToString("0.00") + "\n" +
                       "G: " + rgb.Green.ToString("0.00") + "\n" +
                       "B: " + rgb.Blue.ToString("0.00") + "\n" +
                       "H: " + hsv.Hue.ToString("0.00") + "\n" +
                       "S: " + hsv.Saturation.ToString("0.00") + "\n" +
                       "V: " + hsv.Value.ToString("0.00");
            };

            RGB one = new RGB();
            one.Red = (double)button1.BackColor.R / 255.0f;
            one.Green = (double)button1.BackColor.G / 255.0f;
            one.Blue = (double)button1.BackColor.B / 255.0f;
            HSV oneHSV = ConvertColour(one);
            label1.Text = CreateColourText(one, oneHSV);

            RGB two = new RGB();
            two.Red = (double)button2.BackColor.R / 255.0f;
            two.Green = (double)button2.BackColor.G / 255.0f;
            two.Blue = (double)button2.BackColor.B / 255.0f;
            HSV twoHSV = ConvertColour(two);
            label2.Text = CreateColourText(two, twoHSV);

            int index = 0;
            for (double i = 0.0; i < 1.0; i += 0.1)
            {
                HSV blendHSV = BlendColour(oneHSV, twoHSV, i);
                RGB blend = ConvertColour(blendHSV);
                var colour = Color.FromArgb((int)(blend.Red * 255.0f),
                                            (int)(blend.Green * 255.0f),
                                            (int)(blend.Blue * 255.0f));

                if (m_blendValue <= i && m_blendValue > i - 0.1)
                {
                    button3.BackColor = colour;
                    label3.Text = CreateColourText(blend, blendHSV);
                }

                m_blending[index].BackColor = colour;
                ++index;
            }
        }

        /// <summary>
        /// Updates and sets the blend value
        /// </summary>
        private void SetBlendValue()
        {
            m_blendValue = (double)trackBar1.Value / 100.0f;
            blendValue.Text = m_blendValue.ToString("0.0");
        }

        /// <summary>
        /// On Random button click
        /// </summary>
        private void buttonRandom_Click(object sender, EventArgs e)
        {
            colorDialog1.Color = Color.FromArgb(m_random.Next(255), m_random.Next(255), m_random.Next(255));
            colorDialog2.Color = Color.FromArgb(m_random.Next(255), m_random.Next(255), m_random.Next(255));
            button1.BackColor = colorDialog1.Color;
            button2.BackColor = colorDialog2.Color;
            SetMiddleColour();
        }
    }
}
