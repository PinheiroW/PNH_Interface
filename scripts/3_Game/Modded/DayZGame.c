//======= LoadingScreen =========
modded class LoadingScreen
{
	ref Widget m_WidgetRoot;
	TextWidget m_TextWidgetTitle;
	TextWidget m_TextWidgetStatus;
	TextWidget m_ModdedWarning;
	ImageWidget m_ImageWidgetBackground;
	DayZGame m_DayZGame;
	float m_LastProgressUpdate;
	
	ImageWidget m_ImageLogoMid;
	ImageWidget m_ImageLogoCorner;
	ImageWidget m_ImageLoadingIcon;
	ImageWidget m_ImageBackground;
	VideoWidget m_VideoBackground;
	ProgressBarWidget m_ProgressLoading;
	float m_ImageLoadingIconRotation;
	TextWidget m_ProgressText;
	
	int m_Counter;
	ref Timer m_Timer;
	ref UiHintPanelLoading m_HintPanel;
	
	void LoadingScreen(DayZGame game)
	{
		m_DayZGame = game;
		
		m_WidgetRoot = game.GetLoadingWorkspace().CreateWidgets("PNH_Interface/data/layouts/loading.layout");
		Class.CastTo(m_ImageLogoMid, m_WidgetRoot.FindAnyWidget("ImageLogoMid"));
		Class.CastTo(m_ImageLogoCorner, m_WidgetRoot.FindAnyWidget("ImageLogoCorner"));
		
		Class.CastTo(m_TextWidgetTitle, m_WidgetRoot.FindAnyWidget("TextWidget"));
		Class.CastTo(m_TextWidgetStatus, m_WidgetRoot.FindAnyWidget("StatusText"));
		Class.CastTo(m_ImageWidgetBackground, m_WidgetRoot.FindAnyWidget("ImageBackground"));
		Class.CastTo(m_ImageLoadingIcon, m_WidgetRoot.FindAnyWidget("ImageLoadingIcon"));
		Class.CastTo(m_ModdedWarning, m_WidgetRoot.FindAnyWidget("ModdedWarning"));

		m_ImageBackground = ImageWidget.Cast(m_WidgetRoot.FindAnyWidget("ImageBackground"));
		m_VideoBackground = VideoWidget.Cast(m_WidgetRoot.FindAnyWidget("VideoBackground"));		
		m_ProgressLoading = ProgressBarWidget.Cast(m_WidgetRoot.FindAnyWidget("LoadingBar"));
		
		string tmp;
		m_ProgressText = TextWidget.Cast(m_WidgetRoot.FindAnyWidget("ProgressText"));
		if (GetGame())
		{
			m_ProgressText.Show(GetGame().CommandlineGetParam("loadingTest", tmp));
		}
		
		Widget notification = m_WidgetRoot.FindAnyWidget("notification_root");
		if(notification) notification.Show(false);		
		
		#ifdef PLATFORM_CONSOLE
		#ifdef PLATFORM_XBOX
		#ifdef BUILD_EXPERIMENTAL
		if (notification)
		{
			notification.Show(true);
		}
		#endif
		#endif
		#endif
		
		if(m_ModdedWarning) m_ModdedWarning.Show(g_Game.ReportModded());
		if(m_ImageLogoMid) m_ImageLogoMid.Show(false);
		if(m_ImageLogoCorner) m_ImageLogoCorner.Show(false);
		
		if(m_ImageWidgetBackground) m_ImageWidgetBackground.Show(true);		
		m_Counter = 0;

		// lighten up your desktop
		game.GetBacklit().LoadingAnim();
		
		if(m_ProgressLoading) ProgressAsync.SetProgressData(m_ProgressLoading);
		if(m_ImageBackground) ProgressAsync.SetUserData(m_ImageBackground);
		SetInterface();
	}	
	
	void SetInterface()
	{
		if(m_ProgressLoading) m_ProgressLoading.SetColor(COLOR_PROGRESSBAR);		
		
		// AQUI ESTÁ A MÁGICA PARA REMOVER O TEXTO
		if(!ENABLE_TEXT_MOD_WARNING && m_ModdedWarning) m_ModdedWarning.Show(false);		
		
		if(!ENABLE_VIDEO_LOADSCREEN)
		{
			if(m_VideoBackground) m_VideoBackground.Show(false);	
			if(m_ImageWidgetBackground)
			{
				m_ImageWidgetBackground.Show(true);	
				m_ImageWidgetBackground.LoadImageFile( 0, GetRandomLoadingImg() );
			}
			if(m_ImageBackground) m_ImageBackground.Show(true);
		}
		else
		{
			if(m_ImageWidgetBackground) m_ImageWidgetBackground.Show(false);	
			if(m_ImageBackground) m_ImageBackground.Show(false);
			if(m_VideoBackground)
			{
				m_VideoBackground.Show(true);	
				m_VideoBackground.Load(VIDEO_LOADSCREEN, true);
				m_VideoBackground.Play();
			}
		}		
		if(ENABLE_LOGO_LOADSCREEN && m_ImageLogoMid) 
		{
			m_ImageLogoMid.Show(true);
			m_ImageLogoMid.LoadImageFile( 0, IMAGE_LOGO);
		}
	}	
	
	override void Show()
	{
		Widget lIcon = m_ImageBackground;
		Widget pText = m_ProgressLoading;
		if(m_ProgressText) m_ProgressText.SetText("");
		if(m_ProgressLoading) m_ProgressLoading.SetCurrent(0.0);
		if(m_ImageBackground) m_ImageBackground.SetMaskProgress(0.0);
		
		if (!m_WidgetRoot.IsVisible())
		{
			if (m_DayZGame.GetUIManager().IsDialogVisible())
			{
				m_DayZGame.GetUIManager().HideDialog();
			}
			
			if (m_DayZGame.GetMissionState() == DayZGame.MISSION_STATE_MAINMENU)
			{			
				if(ENABLE_LOGO_LOADSCREEN && m_ImageLogoMid) m_ImageLogoMid.Show(true);			
				if(m_TextWidgetStatus) m_TextWidgetStatus.Show(true);								
			}
			else
			{							
				if(m_ImageLogoMid) m_ImageLogoMid.Show(false);				
				if(m_TextWidgetStatus) m_TextWidgetStatus.Show(false);
			}				
			
			m_WidgetRoot.Show(true);
			if(m_TextWidgetTitle) m_TextWidgetTitle.SetText("");
			if(m_TextWidgetStatus) m_TextWidgetStatus.SetText("");
		}
		
		ProgressAsync.SetProgressData(pText);
		ProgressAsync.SetUserData(lIcon);
	}	
};

modded class LoginQueueBase extends LoginScreenBase
{
	protected TextWidget m_txtPosition;
	protected TextWidget m_txtNote;
	protected ButtonWidget m_btnLeave;
	protected ButtonWidget m_btnSite;
	protected int m_iPosition = -1;	
	protected ImageWidget m_ImageBackground;
	protected VideoWidget m_VideoBackground;	
	
	override Widget Init()
	{		
		layoutRoot 		= GetGame().GetWorkspace().CreateWidgets("PNH_Interface/data/layouts/dialog_queue_position.layout");
		m_HintPanel		= new UiHintPanelLoading(layoutRoot.FindAnyWidget("hint_frame0"));
		m_txtPosition	= TextWidget.Cast(layoutRoot.FindAnyWidget("txtPosition"));
		m_txtNote 		= TextWidget.Cast(layoutRoot.FindAnyWidget("txtNote"));
		m_btnLeave 		= ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnLeave"));		
		m_btnSite		= ButtonWidget.Cast(layoutRoot.FindAnyWidget("ButtonSite"));
		m_ImageBackground = ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));
		m_VideoBackground = VideoWidget.Cast(layoutRoot.FindAnyWidget("VideoBackground"));		
		if(m_txtNote) m_txtNote.Show(true);		
		SetInterface();
		return layoutRoot;
	}
	
	void SetInterface()
	{			
		if(m_btnLeave) m_btnLeave.SetColor(COLOR_HUD);
		if(!ENABLE_BUTTON_QUEUE_URL && m_btnSite) m_btnSite.Show(false);
		
		if(!ENABLE_VIDEO_QUEUE)
		{
			if(m_VideoBackground) m_VideoBackground.Show(false);				
			if(m_ImageBackground)
			{
				m_ImageBackground.Show(true);
				m_ImageBackground.LoadImageFile( 0, GetRandomLoadingImg() );
			}
		}
		else
		{		
			if(m_ImageBackground) m_ImageBackground.Show(false);
			if(m_VideoBackground)
			{
				m_VideoBackground.Show(true);	
				m_VideoBackground.Load(VIDEO_QUEUE, true);
				m_VideoBackground.Play();
			}
		}			
	}	
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);		
		if (w == m_btnSite)
		{
			GetGame().OpenURL(URL_SITE);
			return true;
		}
		return false;
	}
};

modded class LoginTimeBase extends LoginScreenBase
{
	protected TextWidget m_txtDescription;
	protected TextWidget m_txtLabel;
	protected ButtonWidget m_btnLeave;	
	protected bool m_IsRespawn;	
	private ref FullTimeData m_FullTime;	
	protected ImageWidget m_ImageBackground;
	protected VideoWidget m_VideoBackground;	
	
	override Widget Init()
	{
		layoutRoot 			= GetGame().GetWorkspace().CreateWidgets("PNH_Interface/data/layouts/dialog_login_time.layout");		
		m_txtDescription 	= TextWidget.Cast(layoutRoot.FindAnyWidget("txtDescription"));
		m_txtLabel 			= TextWidget.Cast(layoutRoot.FindAnyWidget("txtLabel"));
		m_btnLeave 			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnLeave"));		
		m_ImageBackground 	= ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));
		m_VideoBackground 	= VideoWidget.Cast(layoutRoot.FindAnyWidget("VideoBackground"));		
		if(m_txtDescription) m_txtDescription.Show(true);		
		SetInterface();
		return layoutRoot;
	}
	
	void SetInterface()
	{			
		if(m_btnLeave) m_btnLeave.SetColor(COLOR_HUD);
		
		if(!ENABLE_VIDEO_LOADSCREEN)
		{
			if(m_VideoBackground) m_VideoBackground.Show(false);				
			if(m_ImageBackground)
			{
				m_ImageBackground.Show(true);
				m_ImageBackground.LoadImageFile( 0, GetRandomLoadingImg() );
			}
		}
		else
		{		
			if(m_ImageBackground) m_ImageBackground.Show(false);
			if(m_VideoBackground)
			{
				m_VideoBackground.Show(true);	
				m_VideoBackground.Load(VIDEO_LOADSCREEN, true);
				m_VideoBackground.Play();
			}
		}			
	}	
};

string GetRandomLoadingImg()
{
	// Garante que o array usa as variáveis definidas no ConfigInterface.c
	// Se você só tem 1 imagem, repita ela ou adicione mais definições no config
	private ref array<string> loadingscreens = { IMAGE_LOADINGSCREEN1, IMAGE_LOADINGSCREEN2, IMAGE_LOADINGSCREEN3, IMAGE_LOADINGSCREEN4, IMAGE_LOADINGSCREEN5 };
	int index = Math.RandomInt(0, 100) % 5;	
	return loadingscreens[index];
}