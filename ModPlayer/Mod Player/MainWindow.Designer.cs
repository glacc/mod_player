namespace Mod_Player
{
    partial class MainWindow
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.LoadBtn = new System.Windows.Forms.Button();
            this.FilePathLabel = new System.Windows.Forms.Label();
            this.PlayBtn = new System.Windows.Forms.Button();
            this.PauseBtn = new System.Windows.Forms.Button();
            this.ReplayBtn = new System.Windows.Forms.Button();
            this.StopBtn = new System.Windows.Forms.Button();
            this.InterpolationCB = new System.Windows.Forms.CheckBox();
            this.IsSTKCB = new System.Windows.Forms.CheckBox();
            this.Volume = new System.Windows.Forms.TrackBar();
            this.SongInfoLabel = new System.Windows.Forms.Label();
            this.PrevPat = new System.Windows.Forms.Button();
            this.NextPat = new System.Windows.Forms.Button();
            this.ToolTipInst = new System.Windows.Forms.ToolTip(this.components);
            this.StereoSep = new System.Windows.Forms.TrackBar();
            this.FormTimer = new System.Windows.Forms.Timer(this.components);
            this.VolLabel = new System.Windows.Forms.Label();
            this.SepLabel = new System.Windows.Forms.Label();
            this.AboutLnk = new System.Windows.Forms.LinkLabel();
            ((System.ComponentModel.ISupportInitialize)(this.Volume)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.StereoSep)).BeginInit();
            this.SuspendLayout();
            // 
            // LoadBtn
            // 
            this.LoadBtn.Location = new System.Drawing.Point(272, 11);
            this.LoadBtn.Name = "LoadBtn";
            this.LoadBtn.Size = new System.Drawing.Size(80, 24);
            this.LoadBtn.TabIndex = 0;
            this.LoadBtn.Text = "Load";
            this.LoadBtn.UseVisualStyleBackColor = true;
            this.LoadBtn.Click += new System.EventHandler(this.LoadBtn_Click);
            // 
            // FilePathLabel
            // 
            this.FilePathLabel.Location = new System.Drawing.Point(12, 11);
            this.FilePathLabel.Name = "FilePathLabel";
            this.FilePathLabel.Size = new System.Drawing.Size(254, 24);
            this.FilePathLabel.TabIndex = 1;
            this.FilePathLabel.Text = "Select a module file";
            this.FilePathLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.FilePathLabel.Click += new System.EventHandler(this.LoadBtn_Click);
            // 
            // PlayBtn
            // 
            this.PlayBtn.Enabled = false;
            this.PlayBtn.Location = new System.Drawing.Point(12, 41);
            this.PlayBtn.Name = "PlayBtn";
            this.PlayBtn.Size = new System.Drawing.Size(64, 24);
            this.PlayBtn.TabIndex = 2;
            this.PlayBtn.Text = "Play";
            this.PlayBtn.UseVisualStyleBackColor = true;
            this.PlayBtn.Click += new System.EventHandler(this.PlayBtn_Click);
            // 
            // PauseBtn
            // 
            this.PauseBtn.Enabled = false;
            this.PauseBtn.Location = new System.Drawing.Point(82, 41);
            this.PauseBtn.Name = "PauseBtn";
            this.PauseBtn.Size = new System.Drawing.Size(64, 24);
            this.PauseBtn.TabIndex = 3;
            this.PauseBtn.Text = "Pause";
            this.PauseBtn.UseVisualStyleBackColor = true;
            this.PauseBtn.Click += new System.EventHandler(this.PauseBtn_Click);
            // 
            // ReplayBtn
            // 
            this.ReplayBtn.Enabled = false;
            this.ReplayBtn.Location = new System.Drawing.Point(152, 41);
            this.ReplayBtn.Name = "ReplayBtn";
            this.ReplayBtn.Size = new System.Drawing.Size(64, 24);
            this.ReplayBtn.TabIndex = 4;
            this.ReplayBtn.Text = "Replay";
            this.ReplayBtn.UseVisualStyleBackColor = true;
            this.ReplayBtn.Click += new System.EventHandler(this.ReplayBtn_Click);
            // 
            // StopBtn
            // 
            this.StopBtn.Enabled = false;
            this.StopBtn.Location = new System.Drawing.Point(222, 41);
            this.StopBtn.Name = "StopBtn";
            this.StopBtn.Size = new System.Drawing.Size(64, 24);
            this.StopBtn.TabIndex = 4;
            this.StopBtn.Text = "Stop";
            this.StopBtn.UseVisualStyleBackColor = true;
            this.StopBtn.Click += new System.EventHandler(this.StopBtn_Click);
            // 
            // InterpolationCB
            // 
            this.InterpolationCB.AutoSize = true;
            this.InterpolationCB.Checked = true;
            this.InterpolationCB.CheckState = System.Windows.Forms.CheckState.Checked;
            this.InterpolationCB.Location = new System.Drawing.Point(12, 71);
            this.InterpolationCB.Name = "InterpolationCB";
            this.InterpolationCB.Size = new System.Drawing.Size(102, 16);
            this.InterpolationCB.TabIndex = 5;
            this.InterpolationCB.Text = "Interpolation";
            this.InterpolationCB.UseVisualStyleBackColor = true;
            this.InterpolationCB.CheckedChanged += new System.EventHandler(this.InterpolationCB_CheckedChanged);
            // 
            // IsSTKCB
            // 
            this.IsSTKCB.AutoSize = true;
            this.IsSTKCB.Location = new System.Drawing.Point(12, 90);
            this.IsSTKCB.Name = "IsSTKCB";
            this.IsSTKCB.Size = new System.Drawing.Size(60, 16);
            this.IsSTKCB.TabIndex = 5;
            this.IsSTKCB.Text = "Is STK";
            this.IsSTKCB.UseVisualStyleBackColor = true;
            // 
            // Volume
            // 
            this.Volume.LargeChange = 15;
            this.Volume.Location = new System.Drawing.Point(222, 75);
            this.Volume.Maximum = 255;
            this.Volume.Name = "Volume";
            this.Volume.Size = new System.Drawing.Size(130, 45);
            this.Volume.TabIndex = 6;
            this.Volume.TickFrequency = 32;
            this.ToolTipInst.SetToolTip(this.Volume, "Volume");
            this.Volume.Value = 255;
            this.Volume.Scroll += new System.EventHandler(this.VolumeAdjust);
            // 
            // SongInfoLabel
            // 
            this.SongInfoLabel.Location = new System.Drawing.Point(10, 109);
            this.SongInfoLabel.Name = "SongInfoLabel";
            this.SongInfoLabel.Size = new System.Drawing.Size(181, 23);
            this.SongInfoLabel.TabIndex = 7;
            this.SongInfoLabel.TextAlign = System.Drawing.ContentAlignment.MiddleLeft;
            // 
            // PrevPat
            // 
            this.PrevPat.Location = new System.Drawing.Point(298, 41);
            this.PrevPat.Name = "PrevPat";
            this.PrevPat.Size = new System.Drawing.Size(24, 24);
            this.PrevPat.TabIndex = 8;
            this.PrevPat.Text = "←";
            this.ToolTipInst.SetToolTip(this.PrevPat, "Backward");
            this.PrevPat.UseVisualStyleBackColor = true;
            this.PrevPat.Click += new System.EventHandler(this.PrevPat_Click);
            // 
            // NextPat
            // 
            this.NextPat.Location = new System.Drawing.Point(328, 40);
            this.NextPat.Name = "NextPat";
            this.NextPat.Size = new System.Drawing.Size(24, 24);
            this.NextPat.TabIndex = 8;
            this.NextPat.Text = "→";
            this.ToolTipInst.SetToolTip(this.NextPat, "Forward");
            this.NextPat.UseVisualStyleBackColor = true;
            this.NextPat.Click += new System.EventHandler(this.NextPat_Click);
            // 
            // StereoSep
            // 
            this.StereoSep.LargeChange = 10;
            this.StereoSep.Location = new System.Drawing.Point(222, 110);
            this.StereoSep.Maximum = 100;
            this.StereoSep.Name = "StereoSep";
            this.StereoSep.Size = new System.Drawing.Size(130, 45);
            this.StereoSep.TabIndex = 6;
            this.StereoSep.TickFrequency = 10;
            this.ToolTipInst.SetToolTip(this.StereoSep, "Stereo separation");
            this.StereoSep.Value = 50;
            this.StereoSep.Scroll += new System.EventHandler(this.SeparationAdjust);
            // 
            // FormTimer
            // 
            this.FormTimer.Enabled = true;
            this.FormTimer.Interval = 50;
            this.FormTimer.Tick += new System.EventHandler(this.UpdateSongInfo);
            // 
            // VolLabel
            // 
            this.VolLabel.AutoSize = true;
            this.VolLabel.Location = new System.Drawing.Point(197, 81);
            this.VolLabel.Name = "VolLabel";
            this.VolLabel.Size = new System.Drawing.Size(23, 12);
            this.VolLabel.TabIndex = 9;
            this.VolLabel.Text = "Vol";
            // 
            // SepLabel
            // 
            this.SepLabel.AutoSize = true;
            this.SepLabel.Location = new System.Drawing.Point(197, 114);
            this.SepLabel.Name = "SepLabel";
            this.SepLabel.Size = new System.Drawing.Size(23, 12);
            this.SepLabel.TabIndex = 9;
            this.SepLabel.Text = "Sep";
            // 
            // AboutLnk
            // 
            this.AboutLnk.AutoSize = true;
            this.AboutLnk.Location = new System.Drawing.Point(317, 140);
            this.AboutLnk.Name = "AboutLnk";
            this.AboutLnk.Size = new System.Drawing.Size(35, 12);
            this.AboutLnk.TabIndex = 10;
            this.AboutLnk.TabStop = true;
            this.AboutLnk.Text = "About";
            this.AboutLnk.Click += new System.EventHandler(this.OpenAboutWindow);
            // 
            // MainWindow
            // 
            this.AllowDrop = true;
            this.AutoScaleDimensions = new System.Drawing.SizeF(96F, 96F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Dpi;
            this.ClientSize = new System.Drawing.Size(364, 154);
            this.Controls.Add(this.AboutLnk);
            this.Controls.Add(this.SepLabel);
            this.Controls.Add(this.VolLabel);
            this.Controls.Add(this.NextPat);
            this.Controls.Add(this.PrevPat);
            this.Controls.Add(this.SongInfoLabel);
            this.Controls.Add(this.StereoSep);
            this.Controls.Add(this.Volume);
            this.Controls.Add(this.IsSTKCB);
            this.Controls.Add(this.InterpolationCB);
            this.Controls.Add(this.StopBtn);
            this.Controls.Add(this.ReplayBtn);
            this.Controls.Add(this.PauseBtn);
            this.Controls.Add(this.PlayBtn);
            this.Controls.Add(this.FilePathLabel);
            this.Controls.Add(this.LoadBtn);
            this.DoubleBuffered = true;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.Name = "MainWindow";
            this.Text = "Module Player by Glacc";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.OnFormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.Volume)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.StereoSep)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button LoadBtn;
        private System.Windows.Forms.Label FilePathLabel;
        private System.Windows.Forms.Button PlayBtn;
        private System.Windows.Forms.Button PauseBtn;
        private System.Windows.Forms.Button ReplayBtn;
        private System.Windows.Forms.Button StopBtn;
        private System.Windows.Forms.CheckBox InterpolationCB;
        private System.Windows.Forms.CheckBox IsSTKCB;
        private System.Windows.Forms.TrackBar Volume;
        private System.Windows.Forms.Label SongInfoLabel;
        private System.Windows.Forms.Button PrevPat;
        private System.Windows.Forms.Button NextPat;
        private System.Windows.Forms.ToolTip ToolTipInst;
        private System.Windows.Forms.TrackBar StereoSep;
        private System.Windows.Forms.Timer FormTimer;
        private System.Windows.Forms.Label VolLabel;
        private System.Windows.Forms.Label SepLabel;
        private System.Windows.Forms.LinkLabel AboutLnk;
    }
}

