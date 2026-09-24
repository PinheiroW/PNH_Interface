modded class MainMenu extends UIScriptedMenu
{
	protected DayZIntroScenePC 		m_ScenePC;
	protected TextWidget			m_Version;
	protected TextWidget			m_ModdedWarning;
	protected TextWidget 			m_DevText;
	protected ImageWidget 			m_LogoServer;
	protected ImageWidget			m_character_stats;
	protected VideoWidget 			m_VideoBackground;
	
	protected Widget				m_Play;
	protected Widget		 		m_ChooseServer;
	protected Widget				m_CustomizeCharacter;
	protected Widget				m_SettingsButton;
	protected Widget				m_Exit;
	protected Widget				m_DiscordButton;
	protected Widget 			    m_SiteButton;
	protected Widget				m_play_panel_separator;
	
	protected ref MainMenuStats		m_Stats;
	protected MissionMainMenu		m_Mission;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("PNH_Interface/data/layouts/main_menu.layout");
		
		// Widgets Principais
		m_Play						= layoutRoot.FindAnyWidget("play");
		m_ChooseServer				= layoutRoot.FindAnyWidget("choose_server");
		m_CustomizeCharacter		= layoutRoot.FindAnyWidget("customize_character");
		m_SettingsButton			= layoutRoot.FindAnyWidget("settings_button");
		m_Exit						= layoutRoot.FindAnyWidget("exit_button");
		
		// Widgets Decorativos e Textos
		m_Version					= TextWidget.Cast(layoutRoot.FindAnyWidget("version"));
		m_ModdedWarning				= TextWidget.Cast(layoutRoot.FindAnyWidget("ModdedWarning"));
		m_character_stats			= ImageWidget.Cast(layoutRoot.FindAnyWidget("character_stats_header"));
		m_play_panel_separator		= layoutRoot.FindAnyWidget("play_panel_separator");
		m_DevText   				= TextWidget.Cast(layoutRoot.FindAnyWidget("devtext"));		
		m_LogoServer 				= ImageWidget.Cast(layoutRoot.FindAnyWidget("dayz_logo")); 
		
		// Botões Sociais
		m_DiscordButton				= layoutRoot.FindAnyWidget("discord_button");
		m_SiteButton				= layoutRoot.FindAnyWidget("site_button");
		
		// Background
		m_VideoBackground			= VideoWidget.Cast(layoutRoot.FindAnyWidget("VideoBackground"));		
		
		// Lógica da Cena
		m_Mission					= MissionMainMenu.Cast(GetGame().GetMission());		
		m_ScenePC					= m_Mission.GetIntroScenePC();
		
		if (m_ScenePC) {
			m_ScenePC.ResetIntroCamera();
		}		
		
		// Versão do Jogo
		string version;
		GetGame().GetVersion(version);
		m_Version.SetText("#main_menu_version" + " " + version);		
		
		// Inicialização Visual
		GetGame().GetUIManager().ScreenFadeOut(0);
		SetFocus(null);	
		SetInterface();
		
		// Stats
		if (layoutRoot.FindAnyWidget("character_stats_root"))
		{
			m_Stats	= new MainMenuStats(layoutRoot.FindAnyWidget("character_stats_root"));		
			m_Stats.UpdateStats();
		}
		
		GetDayZGame().GetBacklit().MainMenu_OnShow();
		g_Game.SetLoadState(DayZLoadState.MAIN_MENU_CONTROLLER_SELECT);		
		
		return layoutRoot;
	}
	
	void SetInterface()
	{			
		// Aplica cores definidas no ConfigInterface.c com verificações
		if(m_play_panel_separator) m_play_panel_separator.SetColor(COLOR_HUD);
		if(m_character_stats) m_character_stats.SetColor(COLOR_HUD);
		
		// Configuração de Vídeo de Fundo
		if (m_VideoBackground)
		{
			if (ENABLE_VIDEO_MAINMENU)
			{
				m_VideoBackground.Show(true);
				m_VideoBackground.Load(VIDEO_MAINMENU, true);
				m_VideoBackground.Play();
			}
			else
			{
				m_VideoBackground.Show(false);
			}
		}

		if (m_ModdedWarning) m_ModdedWarning.Show(false);
		if (m_DevText) m_DevText.SetText(TEXT_CREDITS);
		if (m_LogoServer) m_LogoServer.LoadImageFile(0, IMAGE_LOGO);
	}
	
	override void Play()
	{
		// Conexão Direta Otimizada
		if(!ENABLE_CONNECT_IP){
			super.Play();
			return;
		}
		g_Game.ConnectFromServerBrowser(IP_CONNECT, PORT_CONNECT, "");	
	}
	
	override void LoadMods() 
	{
		// Função mantida vazia para otimização (remove carregamento desnecessário)
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (button == MouseState.LEFT)
		{
			if (w == m_DiscordButton)
			{
				GetGame().OpenURL(URL_DISCORD);
				return true;
			}
			if (w == m_SiteButton)
			{
				GetGame().OpenURL(URL_SITE);
				return true;
			}
			if (w == m_Play)
			{
				Play();
				return true;
			}
			if (w == m_Exit)
			{
				Exit();
				return true;
			}
		}
		return super.OnClick(w, x, y, button);
	}
	
	override void ColorHighlight(Widget w)
	{
		if (!w) return;
		ButtonSetColor(w, ARGB(255, 0, 0, 0));
		ButtonSetTextColor(w, COLOR_HUD);
		ImagenSetColor(w, COLOR_HUD);
	}
	
	// Helpers de cor
	void ButtonSetColor(Widget w, int color)
	{
		if (!w) return;
		Widget panel = w.FindWidget(w.GetName() + "_panel");
		if (panel) panel.SetColor(color);
	}
	
	void ImagenSetColor(Widget w, int color)
	{
		if (!w) return;
		Widget panel = w.FindWidget(w.GetName() + "_image");
		if (panel) panel.SetColor(color);
	}
	
	void ButtonSetTextColor(Widget w, int color)
	{
		if (!w) return;
		TextWidget label = TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_label"));
		if (label) label.SetColor(color);
	}
    
    void Exit()
	{
		GetGame().GetUIManager().ShowDialog("#main_menu_exit", "#main_menu_exit_desc", IDC_MAIN_QUIT, DBT_YESNO, DBB_YES, DMT_QUESTION, this);
	}
}