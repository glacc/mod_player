using System;
using System.Runtime.InteropServices;

namespace Glacc.ModPlayer
{
	public class ModPlayer
	{
		[DllImport("LibModPlayer.dll", EntryPoint = "MPLoadModule", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool MPLoadModule(byte[] SongDataOrig, uint SongDataLeng, bool UsingInterpolation, bool IsSTK = false, float TargetStereoSep = 0);

		[DllImport("LibModPlayer.dll", EntryPoint = "MPGetSongName", CallingConvention = CallingConvention.Cdecl)]
		public static extern IntPtr MPGetSongName();

		[DllImport("LibModPlayer.dll", EntryPoint = "MPGetPos", CallingConvention = CallingConvention.Cdecl)]
		public static extern uint MPGetPos();

		[DllImport("LibModPlayer.dll", EntryPoint = "MPPlayModule", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool MPPlayModule();

		[DllImport("LibModPlayer.dll", EntryPoint = "MPPlayPause", CallingConvention = CallingConvention.Cdecl)]
		public static extern void MPPlayPause(bool Value);

		[DllImport("LibModPlayer.dll", EntryPoint = "MPSetPos", CallingConvention = CallingConvention.Cdecl)]
		public static extern void MPSetPos(byte Pos);

		[DllImport("LibModPlayer.dll", EntryPoint = "MPSetVolume", CallingConvention = CallingConvention.Cdecl)]
		public static extern void MPSetVolume(byte Volume);

		[DllImport("LibModPlayer.dll", EntryPoint = "MPResetModule", CallingConvention = CallingConvention.Cdecl)]
		public static extern void MPResetModule();

		[DllImport("LibModPlayer.dll", EntryPoint = "MPStopModule", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool MPStopModule();

		[DllImport("LibModPlayer.dll", EntryPoint = "MPGetExcuteTime", CallingConvention = CallingConvention.Cdecl)]
		public static extern double MPGetExcuteTime();

		[DllImport("LibModPlayer.dll", EntryPoint = "MPSetInterpolation", CallingConvention = CallingConvention.Cdecl)]
		public static extern void MPSetInterpolation(bool UsingInterpolation = true);

		[DllImport("LibModPlayer.dll", EntryPoint = "MPSetSeparation", CallingConvention = CallingConvention.Cdecl)]
		public static extern void MPSetSeparation(float TargetStereoSep);

		[DllImport("LibModPlayer.dll", EntryPoint = "IsPlaying", CallingConvention = CallingConvention.Cdecl)]
		public static extern bool MPIsPlaying();
	}
}