modded class OptionsMenu extends UIScriptedMenu
{		
	protected Widget m_separator_red;
	override Widget Init()
	{
		m_Options		= new GameOptions();
		
		#ifdef PLATFORM_XBOX
		layoutRoot		= GetGame().GetWorkspace().CreateWidgets("gui/layouts/new_ui/options/xbox/options_menu.layout", null);
		#else
		#ifdef PLATFORM_PS4
		layoutRoot		= GetGame().GetWorkspace().CreateWidgets("gui/layouts/new_ui/options/ps/options_menu.layout", null);
		#else
		#ifdef PLATFORM_WINDOWS
		layoutRoot		= GetGame().GetWorkspace().CreateWidgets("gui/layouts/new_ui/options/pc/options_menu.layout", null);
		#endif
		#endif
		#endif
		
		layoutRoot.FindAnyWidget("Tabber").GetScript(m_Tabber);
		
		m_Details		= layoutRoot.FindAnyWidget("settings_details");
		m_Version		= TextWidget.Cast(layoutRoot.FindAnyWidget("version"));
		m_separator_red = layoutRoot.FindAnyWidget("separator_red");
		m_separator_red.SetColor(COLOR_HUD);
		
		m_GameTab		= new OptionsMenuGame(layoutRoot.FindAnyWidget("Tab_0"), m_Details, m_Options, this);
		m_SoundsTab		= new OptionsMenuSounds(layoutRoot.FindAnyWidget("Tab_1"), m_Details, m_Options, this);
		
		#ifdef PLATFORM_XBOX
		m_ControlsTab	= new OptionsMenuControls(layoutRoot.FindAnyWidget("Tab_2"), m_Details, m_Options, this);
		#else
		m_VideoTab		= new OptionsMenuVideo(layoutRoot.FindAnyWidget("Tab_2"), m_Details, m_Options, this);
		m_ControlsTab	= new OptionsMenuControls(layoutRoot.FindAnyWidget("Tab_3"), m_Details, m_Options, this);
		#endif
		
		m_Apply			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("apply"));
		m_Back			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("back"));
		m_Reset			= ButtonWidget.Cast(layoutRoot.FindAnyWidget("reset"));
		m_Defaults		= ButtonWidget.Cast(layoutRoot.FindAnyWidget("defaults"));
		
		m_ModalLock = false;
		m_CanApplyOrReset = false;
		m_CanToggle = false;
		
		string version;
		GetGame().GetVersion(version);
		#ifdef PLATFORM_CONSOLE
		version = "#main_menu_version" + " " + version + " (" + g_Game.GetDatabaseID() + ")";
		#else
		version = "#main_menu_version" + " " + version;
		#endif
		m_Version.SetText(version);
		
		#ifdef PLATFORM_WINDOWS
		SetFocus(layoutRoot);
		#else
		ToggleFocus();
		#endif
		
		m_Tabber.m_OnTabSwitch.Insert(OnTabSwitch);
		m_Tabber.m_OnAttemptTabSwitch.Insert(OnAttemptTabSwitch);
		
		GetGame().GetMission().GetOnInputPresetChanged().Insert(OnInputPresetChanged);
		GetGame().GetMission().GetOnInputDeviceChanged().Insert(OnInputDeviceChanged);
		OnChanged();
		
		return layoutRoot;
	}
		
	override void ColorHighlight(Widget w)
	{
		if (w.IsInherited(ButtonWidget))
		{
			ButtonWidget button = ButtonWidget.Cast(w);
			button.SetTextColor(COLOR_HUD);
		}
		
		w.SetColor(ARGB(255, 0, 0, 0));
		
		TextWidget text1	= TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_text"));
		TextWidget text2	= TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_label"));
		TextWidget text3	= TextWidget.Cast(w.FindAnyWidget(w.GetName() + "_text_1"));		
		ImageWidget image	= ImageWidget.Cast(w.FindAnyWidget(w.GetName() + "_image"));
		Widget option		= Widget.Cast(w.FindAnyWidget(w.GetName() + "_option_wrapper"));
		Widget option_label = w.FindAnyWidget("option_label");
		
		if (text1)
		{
			text1.SetColor(COLOR_HUD);
		}
		
		if (text2)
		{
			text2.SetColor(COLOR_HUD);
		}
		
		if (text3)
		{
			text3.SetColor(COLOR_HUD);
			w.SetAlpha(1);
		}
				
		if (image)
		{
			image.SetColor(COLOR_HUD);
		}
		
		if (option)
		{
			option.SetColor(COLOR_HUD);
		}
		
		if (option_label)
		{
			option_label.SetColor(COLOR_HUD);
		}
	}	
}
