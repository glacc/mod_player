namespace Mod_Player
{
    partial class AboutWindow
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
            this.AboutText = new System.Windows.Forms.Label();
            this.ModArchiveLink = new System.Windows.Forms.LinkLabel();
            this.GetModuleTxt = new System.Windows.Forms.Label();
            this.CloseBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // AboutText
            // 
            this.AboutText.AutoSize = true;
            this.AboutText.Location = new System.Drawing.Point(10, 9);
            this.AboutText.Name = "AboutText";
            this.AboutText.Size = new System.Drawing.Size(221, 36);
            this.AboutText.TabIndex = 0;
            this.AboutText.Text = "Module Player 1.0 by Glacc\r\nLicensed under GPL-3.0\r\nUsed LibModPlayer for playing" +
    " module";
            // 
            // ModArchiveLink
            // 
            this.ModArchiveLink.AutoSize = true;
            this.ModArchiveLink.Location = new System.Drawing.Point(136, 51);
            this.ModArchiveLink.Name = "ModArchiveLink";
            this.ModArchiveLink.Size = new System.Drawing.Size(95, 12);
            this.ModArchiveLink.TabIndex = 1;
            this.ModArchiveLink.TabStop = true;
            this.ModArchiveLink.Text = "The Mod Archive";
            this.ModArchiveLink.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.OpenModArchive);
            // 
            // GetModuleTxt
            // 
            this.GetModuleTxt.AutoSize = true;
            this.GetModuleTxt.Location = new System.Drawing.Point(10, 51);
            this.GetModuleTxt.Name = "GetModuleTxt";
            this.GetModuleTxt.Size = new System.Drawing.Size(107, 12);
            this.GetModuleTxt.TabIndex = 2;
            this.GetModuleTxt.Text = "Link for modules:";
            // 
            // CloseBtn
            // 
            this.CloseBtn.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.CloseBtn.Location = new System.Drawing.Point(92, 69);
            this.CloseBtn.Name = "CloseBtn";
            this.CloseBtn.Size = new System.Drawing.Size(60, 24);
            this.CloseBtn.TabIndex = 3;
            this.CloseBtn.Text = "Close";
            this.CloseBtn.UseVisualStyleBackColor = true;
            this.CloseBtn.Click += new System.EventHandler(this.CloseWindow);
            // 
            // AboutWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.CancelButton = this.CloseBtn;
            this.ClientSize = new System.Drawing.Size(240, 98);
            this.Controls.Add(this.CloseBtn);
            this.Controls.Add(this.GetModuleTxt);
            this.Controls.Add(this.ModArchiveLink);
            this.Controls.Add(this.AboutText);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AboutWindow";
            this.Text = "About";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label AboutText;
        private System.Windows.Forms.LinkLabel ModArchiveLink;
        private System.Windows.Forms.Label GetModuleTxt;
        private System.Windows.Forms.Button CloseBtn;
    }
}