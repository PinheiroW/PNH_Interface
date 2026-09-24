modded class InventoryMenu extends UIScriptedMenu
{		
	override void OnShow()
	{			
		super.OnShow();			
		IngameHud hud = IngameHud.Cast(GetGame().GetMission().GetHud());	
		if( hud )
		{
			hud.HideWatermark();	
		}
	}
	
	override void OnHide()
	{		
		super.OnHide();					
		IngameHud hud = IngameHud.Cast(GetGame().GetMission().GetHud());		
		if( hud )
		{
			hud.ShowWatermark(); 	
		}
	}	
}