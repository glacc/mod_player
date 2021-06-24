using Glacc.ModPlayer;
using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace Mod_Player
{
    public partial class MainWindow : Form
    {
        const string TitleStr = "Module Player by Glacc";
        static string FilePath = "";
        static byte[] SongData;
        static string SongName;
        static FileStream TargetFile;
        static bool ModuleLoaded = false;

        static uint ModInfo;
        static byte ModPos;
        static byte ModPat;
        static byte ModRow;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void OpenAboutWindow(object sender, EventArgs e)
        {
            AboutWindow AboutWind = new AboutWindow();
            AboutWind.Show();
        }

        private void OnFormClosed(object sender, FormClosingEventArgs e)
        {

            ModPlayer.MPStopModule();
        }

        private void LoadBtn_Click(object sender, EventArgs e)
        {
            OpenFileDialog FileSelector = new OpenFileDialog
            {
                Filter = "Module file|*.mod;MOD.*;*.oct;OCT.*|All format|*.*"
            };
            if (FileSelector.ShowDialog() == DialogResult.OK)
            {
                FilePathLabel.Text = FilePath = FileSelector.FileName;

                TargetFile = new FileStream(FilePath, FileMode.Open, FileAccess.Read);

                SongData = new byte[TargetFile.Length];
                TargetFile.Read(SongData, 0, (int)TargetFile.Length);

                ModPlayer.MPStopModule();
                ModuleLoaded = false;

                SongInfoLabel.Text = "";

                TargetFile.Close();

                PlayBtn.Enabled = PauseBtn.Enabled = ReplayBtn.Enabled = StopBtn.Enabled = true;
            }
        }

        private void UpdateSongInfo(object sender, EventArgs e)
        {
            ModInfo = ModPlayer.MPGetPos();
            ModPos = (byte)((ModInfo & 0x00FF0000) >> 16);
            ModPat = (byte)((ModInfo & 0x0000FF00) >> 8);
            ModRow = (byte)(ModInfo & 0x000000FF);

            if (ModPos != 255)
                SongInfoLabel.Text = $"Pos: {ModPos}, Pat: {ModPat}, Row: {ModRow}";
        }

        private void PlayBtn_Click(object sender, EventArgs e)
        {
            if (!ModuleLoaded)
            {
                ModPlayer.MPLoadModule(SongData, (uint)SongData.Length, InterpolationCB.Checked, IsSTKCB.Checked, StereoSep.Value / 100f);
                ModPlayer.MPSetVolume((byte)Volume.Value);

                SongName = Marshal.PtrToStringAnsi(ModPlayer.MPGetSongName());
                Text = $"{TitleStr} - {SongName}";

                ModuleLoaded = true;
            }
            else
            {
                if (!ModPlayer.MPIsPlaying()) ModPlayer.MPPlayPause(true);
            }

            ModPlayer.MPStopModule();
            ModPlayer.MPPlayModule();
        }

        private void PauseBtn_Click(object sender, EventArgs e)
        {
            ModPlayer.MPPlayPause(false);
        }

        private void ReplayBtn_Click(object sender, EventArgs e)
        {
            ModPlayer.MPResetModule();
        }

        private void StopBtn_Click(object sender, EventArgs e)
        {
            ModuleLoaded = false;
            ModPlayer.MPStopModule();
            ModPlayer.MPResetModule();
        }

        private void InterpolationCB_CheckedChanged(object sender, EventArgs e)
        {
            ModPlayer.MPSetInterpolation(InterpolationCB.Checked);
        }

        private void VolumeAdjust(object sender, EventArgs e)
        {
            ModPlayer.MPSetVolume((byte)Volume.Value);
        }

        private void PrevPat_Click(object sender, EventArgs e)
        {
             if (ModPos != 255)
                ModPlayer.MPSetPos((byte)(ModPos - 1));
        }

        private void NextPat_Click(object sender, EventArgs e)
        {
            if (ModPos != 255)
                ModPlayer.MPSetPos((byte)(ModPos + 1));
        }

        private void SeparationAdjust(object sender, EventArgs e)
        {
            ModPlayer.MPSetSeparation(StereoSep.Value / 100f);
        }
    }
}
