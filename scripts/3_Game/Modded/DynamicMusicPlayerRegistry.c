modded class DynamicMusicPlayerRegistry
{	
	//ref array<ref DynamicMusicTrackData> m_TracksMenu;	
	override protected void RegisterTracksMenu()
	{
		m_TracksMenu = new array<ref DynamicMusicTrackData>();
		RegisterTrackMenu("Music_MaiMenu_SoundSet", true); 
	}
}
