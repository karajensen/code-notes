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
    public partial class ToneMapping : Form
    {
        private double m_intensity = 0.0;
        private bool m_initialised = false;
        private List<Button> m_ldr = new List<Button>();
        private ToneMapOperator m_operator;

        enum ToneMapOperator
        {
            REINHARD,
            WHITE_PRESERVING_REINHARD,
            FILMIC
        };

        public ToneMapping()
        {
            InitializeComponent();

            m_ldr.Add(b1);
            m_ldr.Add(b2);
            m_ldr.Add(b3);
            m_ldr.Add(b4);
            m_ldr.Add(b5);
            m_ldr.Add(b6);
            m_ldr.Add(b7);

            colorDialog.Color = Color.FromArgb(255, 128, 64);
            hdrButton.BackColor = colorDialog.Color;

            listBox.Items.Add("Reinhard");
            listBox.Items.Add("White preserving Reinhard");
            listBox.Items.Add("Filmic");
            listBox.SetSelected(1, true);

            m_initialised = true;
            toneMap();
        }

        private void intensity_ValueChanged(object sender, EventArgs e)
        {
            m_intensity = ((double)intensity.Value * (20.0 / 100.0)) - 10.0;
            intensityLbl.Text = m_intensity.ToString("0.0");
            toneMap();
        }

        private void toneMap()
        {
            if(!m_initialised)
            {
                return;
            }

            double intensity = m_intensity - 3.0f;
            double red = (double)hdrButton.BackColor.R / 255.0;
            double green = (double)hdrButton.BackColor.G / 255.0;
            double blue = (double)hdrButton.BackColor.B / 255.0;

            for (int i = 0; i < 7; ++i)
            {
                double gamma = 2.0;
                double exposure = Math.Pow(2.0, intensity);
                double R = red * exposure;
                double G = green * exposure;
                double B = blue * exposure;
                double L = 0.2126 * R + 0.7152 * G + 0.0722 * B;

                if (i == 3)
                {
                    hdrFltLbl.Text =
                        "R: " + R.ToString("0.00000") + "\n" +
                        "G: " + G.ToString("0.00000") + "\n" +
                        "B: " + B.ToString("0.00000");
                }

                if (m_operator == ToneMapOperator.REINHARD)
                {
                    double toneMappedL = L / (1.0 + L);
                    double scale = toneMappedL / L;
                    R = Math.Pow(R * scale, 1.0 / gamma);
                    G = Math.Pow(G * scale, 1.0 / gamma);
                    B = Math.Pow(B * scale, 1.0 / gamma);
                }
                else if (m_operator == ToneMapOperator.WHITE_PRESERVING_REINHARD)
                {
                    double white = 2.0; // smallest luminance that will be mapped to pure white
                    double toneMappedL = L * (1.0 + L / (white * white)) / (1.0 + L);
                    double scale = toneMappedL / L;
                    R = Math.Pow(R * scale, 1.0 / gamma);
                    G = Math.Pow(G * scale, 1.0 / gamma);
                    B = Math.Pow(B * scale, 1.0 / gamma);
                }
                else if (m_operator == ToneMapOperator.FILMIC)
                {
                    R = Math.Max(0.0, R - 0.004);
                    G = Math.Max(0.0, G - 0.004);
                    B = Math.Max(0.0, B - 0.004);
                    R = (R * (6.2 * R + 0.5)) / (R * (6.2 * R + 1.7) + 0.06);
                    G = (G * (6.2 * G + 0.5)) / (G * (6.2 * G + 1.7) + 0.06);
                    B = (B * (6.2 * B + 0.5)) / (B * (6.2 * B + 1.7) + 0.06);
                }

                m_ldr[i].BackColor = Color.FromArgb(
                    Math.Min(Math.Max((int)(R * 255.0), 0), 255),
                    Math.Min(Math.Max((int)(G * 255.0), 0), 255),
                    Math.Min(Math.Max((int)(B * 255.0), 0), 255));

                intensity += 1.0;
            }

            hdrLbl.Text =
                hdrButton.BackColor.R.ToString() + " " +
                hdrButton.BackColor.G.ToString() + " " +
                hdrButton.BackColor.B.ToString();

            ldrLbl.Text =
                b4.BackColor.R.ToString() + " " +
                b4.BackColor.G.ToString() + " " +
                b4.BackColor.B.ToString();
        }

        private void hdrButton_Click(object sender, EventArgs e)
        {
            if (colorDialog.ShowDialog() == DialogResult.OK)
            {
                hdrButton.BackColor = colorDialog.Color;
                toneMap();
            }
        }

        private void listBox_SelectedIndexChanged(object sender, EventArgs e)
        {
            m_operator = (ToneMapOperator)listBox.SelectedIndex;
            toneMap();
        }
    }
}
