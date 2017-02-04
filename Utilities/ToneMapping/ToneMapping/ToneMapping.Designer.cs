namespace WindowsFormsApplication1
{
    partial class ToneMapping
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.colorDialog2 = new System.Windows.Forms.ColorDialog();
            this.button3 = new System.Windows.Forms.Button();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.hdr_color = new System.Windows.Forms.Label();
            this.blendValue = new System.Windows.Forms.Label();
            this.b1 = new System.Windows.Forms.Button();
            this.b2 = new System.Windows.Forms.Button();
            this.b3 = new System.Windows.Forms.Button();
            this.b4 = new System.Windows.Forms.Button();
            this.b5 = new System.Windows.Forms.Button();
            this.b6 = new System.Windows.Forms.Button();
            this.b7 = new System.Windows.Forms.Button();
            this.LDR = new System.Windows.Forms.Label();
            this.HDR = new System.Windows.Forms.Label();
            this.ldr_color = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.hdr_color_flt = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.SuspendLayout();
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(163, 147);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 75);
            this.button3.TabIndex = 2;
            this.button3.UseVisualStyleBackColor = true;
            // 
            // trackBar1
            // 
            this.trackBar1.LargeChange = 10;
            this.trackBar1.Location = new System.Drawing.Point(25, 164);
            this.trackBar1.Maximum = 100;
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(104, 45);
            this.trackBar1.SmallChange = 10;
            this.trackBar1.TabIndex = 3;
            this.trackBar1.Value = 50;
            this.trackBar1.ValueChanged += new System.EventHandler(this.trackBar1_ValueChanged);
            // 
            // hdr_color
            // 
            this.hdr_color.AutoSize = true;
            this.hdr_color.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hdr_color.Location = new System.Drawing.Point(161, 225);
            this.hdr_color.Name = "hdr_color";
            this.hdr_color.Size = new System.Drawing.Size(77, 16);
            this.hdr_color.TabIndex = 5;
            this.hdr_color.Text = "255 255 255";
            this.hdr_color.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // blendValue
            // 
            this.blendValue.AutoSize = true;
            this.blendValue.Location = new System.Drawing.Point(68, 196);
            this.blendValue.Name = "blendValue";
            this.blendValue.Size = new System.Drawing.Size(22, 13);
            this.blendValue.TabIndex = 7;
            this.blendValue.Text = "0.0";
            // 
            // b1
            // 
            this.b1.Location = new System.Drawing.Point(25, 299);
            this.b1.Name = "b1";
            this.b1.Size = new System.Drawing.Size(40, 40);
            this.b1.TabIndex = 8;
            this.b1.UseVisualStyleBackColor = true;
            // 
            // b2
            // 
            this.b2.Location = new System.Drawing.Point(71, 299);
            this.b2.Name = "b2";
            this.b2.Size = new System.Drawing.Size(40, 40);
            this.b2.TabIndex = 9;
            this.b2.UseVisualStyleBackColor = true;
            // 
            // b3
            // 
            this.b3.Location = new System.Drawing.Point(117, 299);
            this.b3.Name = "b3";
            this.b3.Size = new System.Drawing.Size(40, 40);
            this.b3.TabIndex = 10;
            this.b3.UseVisualStyleBackColor = true;
            // 
            // b4
            // 
            this.b4.Location = new System.Drawing.Point(163, 282);
            this.b4.Name = "b4";
            this.b4.Size = new System.Drawing.Size(75, 75);
            this.b4.TabIndex = 11;
            this.b4.UseVisualStyleBackColor = true;
            // 
            // b5
            // 
            this.b5.Location = new System.Drawing.Point(244, 299);
            this.b5.Name = "b5";
            this.b5.Size = new System.Drawing.Size(40, 40);
            this.b5.TabIndex = 12;
            this.b5.UseVisualStyleBackColor = true;
            // 
            // b6
            // 
            this.b6.Location = new System.Drawing.Point(336, 299);
            this.b6.Name = "b6";
            this.b6.Size = new System.Drawing.Size(40, 40);
            this.b6.TabIndex = 13;
            this.b6.UseVisualStyleBackColor = true;
            // 
            // b7
            // 
            this.b7.Location = new System.Drawing.Point(290, 299);
            this.b7.Name = "b7";
            this.b7.Size = new System.Drawing.Size(40, 40);
            this.b7.TabIndex = 14;
            this.b7.UseVisualStyleBackColor = true;
            // 
            // LDR
            // 
            this.LDR.AutoSize = true;
            this.LDR.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LDR.Location = new System.Drawing.Point(182, 263);
            this.LDR.Name = "LDR";
            this.LDR.Size = new System.Drawing.Size(35, 16);
            this.LDR.TabIndex = 20;
            this.LDR.Text = "LDR";
            this.LDR.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // HDR
            // 
            this.HDR.AutoSize = true;
            this.HDR.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.HDR.Location = new System.Drawing.Point(180, 130);
            this.HDR.Name = "HDR";
            this.HDR.Size = new System.Drawing.Size(38, 16);
            this.HDR.TabIndex = 21;
            this.HDR.Text = "HDR";
            this.HDR.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // ldr_color
            // 
            this.ldr_color.AutoSize = true;
            this.ldr_color.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ldr_color.Location = new System.Drawing.Point(161, 360);
            this.ldr_color.Name = "ldr_color";
            this.ldr_color.Size = new System.Drawing.Size(77, 16);
            this.ldr_color.TabIndex = 22;
            this.ldr_color.Text = "255 255 255";
            this.ldr_color.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(35, 145);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(94, 16);
            this.label1.TabIndex = 23;
            this.label1.Text = "Intensity Stops";
            this.label1.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(30, 345);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 16);
            this.label2.TabIndex = 24;
            this.label2.Text = "-3.0";
            this.label2.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(77, 345);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(29, 16);
            this.label3.TabIndex = 25;
            this.label3.Text = "-2.0";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(123, 345);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(29, 16);
            this.label4.TabIndex = 26;
            this.label4.Text = "-1.0";
            this.label4.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(343, 345);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(32, 16);
            this.label5.TabIndex = 29;
            this.label5.Text = "+3.0";
            this.label5.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(297, 345);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(32, 16);
            this.label6.TabIndex = 28;
            this.label6.Text = "+2.0";
            this.label6.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(250, 345);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(32, 16);
            this.label7.TabIndex = 27;
            this.label7.Text = "+1.0";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Items.AddRange(new object[] {
            "Linear",
            "Reinhard",
            "Luma-based Reinhard",
            "White preserving luma-based Reinhard",
            "Filmic"});
            this.listBox1.Location = new System.Drawing.Point(102, 12);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(205, 95);
            this.listBox1.TabIndex = 30;
            // 
            // hdr_color_flt
            // 
            this.hdr_color_flt.AutoSize = true;
            this.hdr_color_flt.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hdr_color_flt.Location = new System.Drawing.Point(297, 147);
            this.hdr_color_flt.Name = "hdr_color_flt";
            this.hdr_color_flt.Size = new System.Drawing.Size(41, 48);
            this.hdr_color_flt.TabIndex = 31;
            this.hdr_color_flt.Text = "R: 0.0\r\nG: 0.0\r\nB: 0.0";
            this.hdr_color_flt.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // ToneMapping
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(408, 395);
            this.Controls.Add(this.hdr_color_flt);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ldr_color);
            this.Controls.Add(this.HDR);
            this.Controls.Add(this.LDR);
            this.Controls.Add(this.b7);
            this.Controls.Add(this.b6);
            this.Controls.Add(this.b5);
            this.Controls.Add(this.b4);
            this.Controls.Add(this.b3);
            this.Controls.Add(this.b2);
            this.Controls.Add(this.b1);
            this.Controls.Add(this.blendValue);
            this.Controls.Add(this.hdr_color);
            this.Controls.Add(this.trackBar1);
            this.Controls.Add(this.button3);
            this.Name = "ToneMapping";
            this.Text = "Colour Converter";
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.ColorDialog colorDialog2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.TrackBar trackBar1;
        private System.Windows.Forms.Label hdr_color;
        private System.Windows.Forms.Label blendValue;
        private System.Windows.Forms.Button b1;
        private System.Windows.Forms.Button b2;
        private System.Windows.Forms.Button b3;
        private System.Windows.Forms.Button b4;
        private System.Windows.Forms.Button b5;
        private System.Windows.Forms.Button b6;
        private System.Windows.Forms.Button b7;
        private System.Windows.Forms.Label LDR;
        private System.Windows.Forms.Label HDR;
        private System.Windows.Forms.Label ldr_color;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label hdr_color_flt;
    }
}

