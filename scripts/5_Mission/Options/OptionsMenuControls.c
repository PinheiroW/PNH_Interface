modded class OptionsMenuControls extends ScriptedWidgetEventHandler
{			
	override void ColorRed( Widget w )
	{
		SetFocus( w );
		ButtonWidget button;
		if (Class.CastTo(button,w))
		{
			button.SetTextColor( COLOR_HUD );
			button.SetAlpha( 0.9 );
		}
	}	
}