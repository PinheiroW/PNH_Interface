modded class LogoutMenu extends UIScriptedMenu
{	
	protected Widget m_SeparatorPanel;
	
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("gui/layouts/day_z_logout_dialog.layout");	
		
		m_LogoutTimeText 	= TextWidget.Cast(layoutRoot.FindAnyWidget("txtLogoutTime"));
		m_DescriptionText 	= TextWidget.Cast(layoutRoot.FindAnyWidget("txtDescription"));
		m_bLogoutNow 		= ButtonWidget.Cast(layoutRoot.FindAnyWidget("bLogoutNow"));
		m_bCancel 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("bCancel"));	
		
		// Customização Visual
		m_SeparatorPanel	= layoutRoot.FindAnyWidget("SeparatorPanel");		
		if (m_SeparatorPanel) m_SeparatorPanel.SetColor(COLOR_HUD);
		
		if (m_bLogoutNow)
		{
			m_bLogoutNow.SetColor(COLOR_HUD);
			m_bLogoutNow.Show(ENABLE_LOGOUT_NOW);
		}
		
		if (m_bCancel)
		{
			m_bCancel.SetColor(COLOR_HUD);
		}
		
		UpdateInfo();			
		
		// Lógica Segura de Emote
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player)
		{
			// Checa se tem emote manager, se não está preso, desmaiado, em veículo ou nadando
			if (player.GetEmoteManager() && !player.IsRestrained() && !player.IsUnconscious() && !player.GetCommand_Vehicle() && !player.GetCommand_Swim()) 
			{
				player.GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_SITA);
				player.GetEmoteManager().GetEmoteLauncher().SetForced(EmoteLauncher.FORCE_DIFFERENT);
			}
		}		
		return layoutRoot;
	}	
}