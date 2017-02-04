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
            this.colorDialog = new System.Windows.Forms.ColorDialog();
            this.hdrButton = new System.Windows.Forms.Button();
            this.intensity = new System.Windows.Forms.TrackBar();
            this.hdrLbl = new System.Windows.Forms.Label();
            this.intensityLbl = new System.Windows.Forms.Label();
            this.b1 = new System.Windows.Forms.Button();
            this.b2 = new System.Windows.Forms.Button();
            this.b3 = new System.Windows.Forms.Button();
            this.b4 = new System.Windows.Forms.Button();
            this.b5 = new System.Windows.Forms.Button();
            this.b6 = new System.Windows.Forms.Button();
            this.b7 = new System.Windows.Forms.Button();
            this.LDR = new System.Windows.Forms.Label();
            this.HDR = new System.Windows.Forms.Label();
            this.ldrLbl = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.listBox = new System.Windows.Forms.ListBox();
            this.hdrFltLbl = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.intensity)).BeginInit();
            this.SuspendLayout();
            // 
            // hdrButton
            // 
            this.hdrButton.Location = new System.Drawing.Point(166, 102);
            this.hdrButton.Name = "hdrButton";
            this.hdrButton.Size = new System.Drawing.Size(75, 75);
            this.hdrButton.TabIndex = 2;
            this.hdrButton.UseVisualStyleBackColor = true;
            this.hdrButton.Click += new System.EventHandler(this.hdrButton_Click);
            // 
            // intensity
            // 
            this.intensity.LargeChange = 10;
            this.intensity.Location = new System.Drawing.Point(28, 119);
            this.intensity.Maximum = 100;
            this.intensity.Name = "intensity";
            this.intensity.Size = new System.Drawing.Size(104, 45);
            this.intensity.SmallChange = 10;
            this.intensity.TabIndex = 3;
            this.intensity.Value = 50;
            this.intensity.ValueChanged += new System.EventHandler(this.intensity_ValueChanged);
            // 
            // hdrLbl
            // 
            this.hdrLbl.AutoSize = true;
            this.hdrLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hdrLbl.Location = new System.Drawing.Point(164, 180);
            this.hdrLbl.Name = "hdrLbl";
            this.hdrLbl.Size = new System.Drawing.Size(77, 16);
            this.hdrLbl.TabIndex = 5;
            this.hdrLbl.Text = "255 255 255";
            this.hdrLbl.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // intensityLbl
            // 
            this.intensityLbl.AutoSize = true;
            this.intensityLbl.Location = new System.Drawing.Point(71, 151);
            this.intensityLbl.Name = "intensityLbl";
            this.intensityLbl.Size = new System.Drawing.Size(22, 13);
            this.intensityLbl.TabIndex = 7;
            this.intensityLbl.Text = "0.0";
            // 
            // b1
            // 
            this.b1.Location = new System.Drawing.Point(28, 254);
            this.b1.Name = "b1";
            this.b1.Size = new System.Drawing.Size(40, 40);
            this.b1.TabIndex = 8;
            this.b1.UseVisualStyleBackColor = true;
            // 
            // b2
            // 
            this.b2.Location = new System.Drawing.Point(74, 254);
            this.b2.Name = "b2";
            this.b2.Size = new System.Drawing.Size(40, 40);
            this.b2.TabIndex = 9;
            this.b2.UseVisualStyleBackColor = true;
            // 
            // b3
            // 
            this.b3.Location = new System.Drawing.Point(120, 254);
            this.b3.Name = "b3";
            this.b3.Size = new System.Drawing.Size(40, 40);
            this.b3.TabIndex = 10;
            this.b3.UseVisualStyleBackColor = true;
            // 
            // b4
            // 
            this.b4.Location = new System.Drawing.Point(166, 237);
            this.b4.Name = "b4";
            this.b4.Size = new System.Drawing.Size(75, 75);
            this.b4.TabIndex = 11;
            this.b4.UseVisualStyleBackColor = true;
            // 
            // b5
            // 
            this.b5.Location = new System.Drawing.Point(247, 254);
            this.b5.Name = "b5";
            this.b5.Size = new System.Drawing.Size(40, 40);
            this.b5.TabIndex = 12;
            this.b5.UseVisualStyleBackColor = true;
            // 
            // b6
            // 
            this.b6.Location = new System.Drawing.Point(338, 254);
            this.b6.Name = "b6";
            this.b6.Size = new System.Drawing.Size(40, 40);
            this.b6.TabIndex = 13;
            this.b6.UseVisualStyleBackColor = true;
            // 
            // b7
            // 
            this.b7.Location = new System.Drawing.Point(293, 254);
            this.b7.Name = "b7";
            this.b7.Size = new System.Drawing.Size(40, 40);
            this.b7.TabIndex = 14;
            this.b7.UseVisualStyleBackColor = true;
            // 
            // LDR
            // 
            this.LDR.AutoSize = true;
            this.LDR.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.LDR.Location = new System.Drawing.Point(185, 218);
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
            this.HDR.Location = new System.Drawing.Point(183, 85);
            this.HDR.Name = "HDR";
            this.HDR.Size = new System.Drawing.Size(38, 16);
            this.HDR.TabIndex = 21;
            this.HDR.Text = "HDR";
            this.HDR.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // ldrLbl
            // 
            this.ldrLbl.AutoSize = true;
            this.ldrLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ldrLbl.Location = new System.Drawing.Point(164, 315);
            this.ldrLbl.Name = "ldrLbl";
            this.ldrLbl.Size = new System.Drawing.Size(77, 16);
            this.ldrLbl.TabIndex = 22;
            this.ldrLbl.Text = "255 255 255";
            this.ldrLbl.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(38, 100);
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
            this.label2.Location = new System.Drawing.Point(33, 300);
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
            this.label3.Location = new System.Drawing.Point(79, 300);
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
            this.label4.Location = new System.Drawing.Point(125, 300);
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
            this.label5.Location = new System.Drawing.Point(342, 300);
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
            this.label6.Location = new System.Drawing.Point(297, 300);
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
            this.label7.Location = new System.Drawing.Point(251, 300);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(32, 16);
            this.label7.TabIndex = 27;
            this.label7.Text = "+1.0";
            this.label7.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // listBox
            // 
            this.listBox.FormattingEnabled = true;
            this.listBox.Location = new System.Drawing.Point(102, 12);
            this.listBox.Name = "listBox";
            this.listBox.Size = new System.Drawing.Size(205, 56);
            this.listBox.TabIndex = 30;
            this.listBox.SelectedIndexChanged += new System.EventHandler(this.listBox_SelectedIndexChanged);
            // 
            // hdrFltLbl
            // 
            this.hdrFltLbl.AutoSize = true;
            this.hdrFltLbl.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hdrFltLbl.Location = new System.Drawing.Point(277, 102);
            this.hdrFltLbl.Name = "hdrFltLbl";
            this.hdrFltLbl.Size = new System.Drawing.Size(41, 48);
            this.hdrFltLbl.TabIndex = 31;
            this.hdrFltLbl.Text = "R: 0.0\r\nG: 0.0\r\nB: 0.0";
            this.hdrFltLbl.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // ToneMapping
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(408, 349);
            this.Controls.Add(this.hdrFltLbl);
            this.Controls.Add(this.listBox);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.ldrLbl);
            this.Controls.Add(this.HDR);
            this.Controls.Add(this.LDR);
            this.Controls.Add(this.b7);
            this.Controls.Add(this.b6);
            this.Controls.Add(this.b5);
            this.Controls.Add(this.b4);
            this.Controls.Add(this.b3);
            this.Controls.Add(this.b2);
            this.Controls.Add(this.b1);
            this.Controls.Add(this.intensityLbl);
            this.Controls.Add(this.hdrLbl);
            this.Controls.Add(this.intensity);
            this.Controls.Add(this.hdrButton);
            this.Name = "ToneMapping";
            this.Text = "Colour Converter";
            ((System.ComponentModel.ISupportInitialize)(this.intensity)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ColorDialog colorDialog;
        private System.Windows.Forms.Button hdrButton;
        private System.Windows.Forms.TrackBar intensity;
        private System.Windows.Forms.Label hdrLbl;
        private System.Windows.Forms.Label intensityLbl;
        private System.Windows.Forms.Button b1;
        private System.Windows.Forms.Button b2;
        private System.Windows.Forms.Button b3;
        private System.Windows.Forms.Button b4;
        private System.Windows.Forms.Button b5;
        private System.Windows.Forms.Button b6;
        private System.Windows.Forms.Button b7;
        private System.Windows.Forms.Label LDR;
        private System.Windows.Forms.Label HDR;
        private System.Windows.Forms.Label ldrLbl;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.ListBox listBox;
        private System.Windows.Forms.Label hdrFltLbl;
    }
}

