modded class MissionGameplay extends MissionBase
{	
	override void OnUpdate(float timeslice)
	{		 
		super.OnUpdate(timeslice);
		
		Input input = GetGame().GetInput();
		// Verifica se o Input foi pressionado e se m_Hud existe antes de chamar a função
		if(input && input.LocalPress("PNH_ToggleWatermark", false))
		{
			if (m_Hud)
			{
				m_Hud.ToggleLogo();		
			}
		}
    }
}