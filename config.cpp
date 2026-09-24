class CfgPatches
{
	class PNHInterface
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class PNHInterface
	{
		dir="PNH_Interface";
		hideName=1;
		hidePicture=1;
		name="PNHInterface";
		credits="PNH";
		author="Pinheiro";
		version="1.0";
		type="mod";
		inputs="PNH_Interface/inputs/inputs.xml";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"PNH_Interface/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"PNH_Interface/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"PNH_Interface/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgSoundSets
{
	class Music_MaiMenu_SoundSet
	{
		soundShaders[]=
		{
			"Music_MainMenu_SoundShader"
		};
		volumeFactor=1;
		frequencyFactor=1;
		spatial=0;
	};
};
class CfgSoundShaders
{
	class Music_MainMenu_SoundShader
	{
		samples[]=
		{
			
			{
				"\PNH_Interface\data\sound\mainmenu",
				1
			}
		};
		volume=0.5;
	};
};
