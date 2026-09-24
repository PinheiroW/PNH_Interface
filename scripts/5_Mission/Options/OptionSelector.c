modded class OptionSelectorSliderSetup extends OptionSelectorBase
{		
	override void ColorHighlight(Widget w)
	{		
		if (!w) return;
		if (m_Slider)
		{
			SetFocus(m_Slider);
			m_Slider.SetColor(COLOR_HUD);
		}				
	}		
}

modded class OptionSelectorBase extends ScriptedWidgetEventHandler
{
	override void ColorHighlight(Widget w)
	{
		if(!w) return;
		ButtonSetColor(w, COLOR_HUD);
	}
	
	override void ColorHighlightConsole(Widget w)
	{
		if(!w) return;
		int color_pnl = COLOR_HUD;
		int color_lbl = ARGB(255, 255, 255, 255);
		
		ButtonSetColorConsole(w, color_pnl);
		ButtonSetAlphaAnimConsole(null);
		ButtonSetTextColorConsole(w, color_lbl);
	}
}