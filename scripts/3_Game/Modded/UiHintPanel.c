modded class UiHintPanel extends ScriptedWidgetEventHandler
{		
	protected const string m_DataPathNew = "PNH_Interface/data/loadingStatus.json";	 	
	override protected void LoadContentList(){
		JsonFileLoader<array<ref HintPage>>.JsonLoadFile( m_DataPathNew, m_ContentList );
	}	
}

