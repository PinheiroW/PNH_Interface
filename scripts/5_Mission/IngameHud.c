modded class IngameHud
{
	protected Widget layoutWatermark;
    ImageWidget watermark;
    bool m_LogoVisible = true;

	override void Init(Widget hud_panel_widget)
	{
        super.Init(hud_panel_widget);		
        layoutWatermark = GetGame().GetWorkspace().CreateWidgets("PNH_Interface/data/layouts/watermark.layout");
		watermark = ImageWidget.Cast(layoutWatermark.FindAnyWidget("logo"));
		if(ENABLE_WATERMARK)
		{
			watermark.LoadImageFile(0, IMAGE_WATERMARK);
       		watermark.Show(true);
		}
		else
		{
			watermark.Show(false);
		}
    }

    void ToggleLogo()
    {
		if(ENABLE_WATERMARK)
		{
	        if (!m_LogoVisible)
			{
				m_LogoVisible = true;
	            ShowWatermark();
	        }			
			else
			{
				m_LogoVisible = false;
	            HideWatermark();
			}	
		}	
    }
	
	void HideWatermark()
	{
		layoutWatermark.Show(false);
	}
	
	void ShowWatermark()
	{
		if(m_LogoVisible)
		{
			layoutWatermark.Show(true);	
		}
	}
}

