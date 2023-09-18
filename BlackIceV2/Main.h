#define Main
#define dfltMax (17)

/* Please respect my work and leave this header here, thank you.

	MENU BASE CREATED BY: 0x0000000
	CREDITS: 0x0000000, seb5594, anyone else that may have been forgotten

*/

/*Tips:
- If you wish to decrease the amount of sub menus remember to decrease the number above to the amount of sub menus you have. #define dfltMax (submenu count here)
- Always use HandleScrolling(clientnumber) after creating a new sub menu.
- Always use RESET_BTN(clientnumber) when using button monitoring otherwise it will keep returning true as you hold the button down.
  Resetting the button is better than using sleep because sleep will slow down the plugin
- Create new variables inside structures, so if you make a new function to give e.g godmode, put the boolean check for godmode inside the Client struct
  which can be located in Game.h at the very top. Same thing for anything related to the menu_structure.
  Like this:
  struct Client {
	bool Godmode;
	bool Noclip;
  } client_t[18];

- To change the text in sub menus/add more, go right below the menu_structure struct and look for the SubMenu ID you want to change.
  It's numbered the same way the MenuID's are.


 *NOTE* LEAVE THE FIRST STRING OF EACH SUBMENU EMPTY, TOO LAZY TO FIX *NOTE*
*/

//cl = clientnumber
//variables
bool unfairAimbot[18];
bool spawnBots;
bool timeToThink;
int theme[18];
int r;
int hostClientNumber = 0;

struct menu_structure {
	game_hudelem_s* Options[18], *Title;
	int MenuID;
	int ScrollID;
	int MenuScroll;
	int MaxScroll;
	int clScroll;
	bool isLoaded;
	bool isOpen;
} menu_s[18];

#pragma region sub_menus
//*NOTE* LEAVE THE FIRST STRING OF EACH SUBMENU EMPTY, TOO LAZY TO FIX *NOTE*
	char* MainMenu[18] = { "", /*1*/"Main Mods", /*2*/"Fun Menu", /*3*/"Lobby Menu", /*4*/"Message Menu", //Main Menu (MenuID: 0)
		/*5*/"All Players", /*6*/"Weapons", /*7*/"Account", /*8*/"Host Menu", /*9*/"Menu Settings", 
		/*10*/"Players", "", "", "", "", "", "", "" };
	char* SubMenu1[18] = { "", "God Mode", "No Clip", "Infinite Ammo", "Little Crosshair", //Sub Menu 1 (MenuID: 1)
		"No Recoil", "Red Boxes", "Explosive Bullets", "Aim Assist", "Change Name", "", "", "", "", "", "", "", "" };
	char* SubMenu2[18] = { "", "Double Run Speed", "FOV", "Pro Skater", "Third Person", //Sub Menu 2 (MenuID: 2)
		"Left Hand Gun", "", "", "", "", "", "", "", "", "", "", "", "" };
	char* SubMenu3[18] = { "", "High Jump", "Super Speed", "Force Host", "Super Force Host", //Sub Menu 3 (MenuID: 3)
		"Gravity", "TimeScale", "Super Melee", "Allow End Game", "Disable End Game", "", "", "", "", "", "", "", "" };
	char* SubMenu4[18] = { "", "Creators", "TrickShot Last", "Custom", "", //Sub Menu 4 (MenuID: 4)
		"", "", "", "", "", "", "", "", "", "", "", "", "" };
	char* SubMenu5[18] = { "", "God Mode", "No Clip", "Red Boxes", "3rd Person", //Sub Menu 5 (MenuID: 5)
		"FOV", "Infite Ammo", "Level 70", "Unlock All", "", "", "", "", "", "", "", "", "" };
	char* SubMenu6[18] = { "", "AC130", "Intervention", "Barrett", "Gold Deagle", //Sub Menu 6 (MenuID: 6)
		"Default Weapon", "", "", "", "", "", "", "", "", "", "", "", "" };
	char* SubMenu7[18] = { "", "Level 70", "Unlock All", "Toggle Prestige", "^5B^7lack^5I^7ce ClanTag {BI}", //Sub Menu 7 (MenuID: 7)
		"", "", "", "", "", "", "", "", "", "", "", "", "" };
	char* SubMenu8[18] = { "", "Unfair Aimbot","Spawn 3 Bots","Spawn Bot","Unlimited Game",
		"Restart Game","Maps","","","","", "", "", "", "", "", "", "" };
	char* SubMenu9[18] = { "", "Default Theme", "Red Theme", "Orange Theme", "Yellow Theme", //Sub Menu 9 (MenuID: 9)
		"Green Theme", "Cyan Theme", "Blue Theme", "Purple Theme", "Pink Theme", "White Theme", "", "", "", "", "", "", "" };
	//Player Menu is not here, don't remove it unless you know what you're doing
	char* ClientMenu[18] = { "", "Give Admin", "Give VIP", "Give Verified", "Remove Access", //Client Menu (MenuID: 99)
		"Kick Client", "", "", "", "", "", "", "", "", "", "", "", "" };

	char* MapsMenu[18] = { "", "Afghan", "Derail", "Estate", "Favela", //Maps Menu (MenuID: 11)
		"Highrise", "Invasion", "Karachi", "Quarry", "Rundown", "Rust", "Scrapyard", 
		"Skidrow", "Sub Base", "Terminal", "Underpass", "Wasteland", "" };
#pragma endregion

struct new_menu {
	const char* Options[18];
	const char* Title;
	int MenuID;
	int maxScroll;
	int curScroll;
} new_menu_t[18];

void Update(int cl) {
	menu_s[cl].MaxScroll = new_menu_t[cl].maxScroll;
	menu_s[cl].MenuID = new_menu_t[cl].MenuID;
	menu_s[cl].MenuScroll = new_menu_t[cl].MenuID;
	menu_s[cl].ScrollID = new_menu_t[cl].curScroll;
	
	r = G_irand(1, 9);
	if(theme[cl] == 0)
		menu_s[cl].Title->elem.color.r = randRGB(r,1),menu_s[cl].Title->elem.color.g = randRGB(r,2),menu_s[cl].Title->elem.color.b = randRGB(r,3),menu_s[cl].Title->elem.glowColor.r = randRGB(r,1), menu_s[cl].Title->elem.glowColor.g = randRGB(r,2), menu_s[cl].Title->elem.glowColor.b = randRGB(r,3),menu_s[cl].Title->elem.glowColor.a = 5;
	else if(theme[cl] == 1)
		menu_s[cl].Title->elem.color.r = randRGB(1,1),menu_s[cl].Title->elem.color.g = randRGB(1,2),menu_s[cl].Title->elem.color.b = randRGB(1,3),menu_s[cl].Title->elem.glowColor.r = randRGB(1,1), menu_s[cl].Title->elem.glowColor.g = randRGB(1,2), menu_s[cl].Title->elem.glowColor.b = randRGB(1,3),menu_s[cl].Title->elem.glowColor.a = 5;
	else if(theme[cl] == 2)
		menu_s[cl].Title->elem.color.r = randRGB(2,1),menu_s[cl].Title->elem.color.g = randRGB(2,2),menu_s[cl].Title->elem.color.b = randRGB(2,3),menu_s[cl].Title->elem.glowColor.r = randRGB(2,1), menu_s[cl].Title->elem.glowColor.g = randRGB(2,2), menu_s[cl].Title->elem.glowColor.b = randRGB(2,3),menu_s[cl].Title->elem.glowColor.a = 5;
	else if(theme[cl] == 3)
		menu_s[cl].Title->elem.color.r = randRGB(3,1),menu_s[cl].Title->elem.color.g = randRGB(3,2),menu_s[cl].Title->elem.color.b = randRGB(3,3),menu_s[cl].Title->elem.glowColor.r = randRGB(3,1), menu_s[cl].Title->elem.glowColor.g = randRGB(3,2), menu_s[cl].Title->elem.glowColor.b = randRGB(3,3),menu_s[cl].Title->elem.glowColor.a = 5;
	else if(theme[cl] == 4)
		menu_s[cl].Title->elem.color.r = randRGB(4,1),menu_s[cl].Title->elem.color.g = randRGB(4,2),menu_s[cl].Title->elem.color.b = randRGB(4,3),menu_s[cl].Title->elem.glowColor.r = randRGB(4,1), menu_s[cl].Title->elem.glowColor.g = randRGB(4,2), menu_s[cl].Title->elem.glowColor.b = randRGB(4,3),menu_s[cl].Title->elem.glowColor.a = 5;
	else if(theme[cl] == 5)
		menu_s[cl].Title->elem.color.r = randRGB(5,1),menu_s[cl].Title->elem.color.g = randRGB(5,2),menu_s[cl].Title->elem.color.b = randRGB(5,3),menu_s[cl].Title->elem.glowColor.r = randRGB(5,1), menu_s[cl].Title->elem.glowColor.g = randRGB(5,2), menu_s[cl].Title->elem.glowColor.b = randRGB(5,3),menu_s[cl].Title->elem.glowColor.a = 5;
	else if(theme[cl] == 6)
		menu_s[cl].Title->elem.color.r = randRGB(6,1),menu_s[cl].Title->elem.color.g = randRGB(6,2),menu_s[cl].Title->elem.color.b = randRGB(6,3),menu_s[cl].Title->elem.glowColor.r = randRGB(6,1), menu_s[cl].Title->elem.glowColor.g = randRGB(6,2), menu_s[cl].Title->elem.glowColor.b = randRGB(6,3),menu_s[cl].Title->elem.glowColor.a = 5;
	else if(theme[cl] == 7)
		menu_s[cl].Title->elem.color.r = randRGB(7,1),menu_s[cl].Title->elem.color.g = randRGB(7,2),menu_s[cl].Title->elem.color.b = randRGB(7,3),menu_s[cl].Title->elem.glowColor.r = randRGB(7,1), menu_s[cl].Title->elem.glowColor.g = randRGB(7,2), menu_s[cl].Title->elem.glowColor.b = randRGB(7,3),menu_s[cl].Title->elem.glowColor.a = 5;
	else if(theme[cl] == 8)
		menu_s[cl].Title->elem.color.r = randRGB(8,1),menu_s[cl].Title->elem.color.g = randRGB(8,2),menu_s[cl].Title->elem.color.b = randRGB(8,3),menu_s[cl].Title->elem.glowColor.r = randRGB(8,1), menu_s[cl].Title->elem.glowColor.g = randRGB(8,2), menu_s[cl].Title->elem.glowColor.b = randRGB(8,3),menu_s[cl].Title->elem.glowColor.a = 5;
	else if(theme[cl] == 9)
		menu_s[cl].Title->elem.color.r = randRGB(9,1),menu_s[cl].Title->elem.color.g = randRGB(9,2),menu_s[cl].Title->elem.color.b = randRGB(9,3),menu_s[cl].Title->elem.glowColor.r = randRGB(9,1), menu_s[cl].Title->elem.glowColor.g = randRGB(9,2), menu_s[cl].Title->elem.glowColor.b = randRGB(9,3),menu_s[cl].Title->elem.glowColor.a = 5;

	ChangeText(menu_s[cl].Title, (char*)new_menu_t[cl].Title);
	for (int i = 0; i < 18; i++)
		ChangeText(menu_s[cl].Options[i], (char*)new_menu_t[cl].Options[i]);
}

new_menu New_Menu(int cl, Access Minimum, int MenuID, int maxScroll, int curScroll, const char* title, const char* Options[18])
{
	char accessBuf[100];
	snprintf(accessBuf, sizeof(accessBuf), "^1Access Denied: ^7%s or higher required", AccessString(Minimum));
	if (hasAccess(cl, Minimum))
	{
		for (int i = 0; i < 18; i++)
			new_menu_t[cl].Options[i] = Options[i];
		new_menu_t[cl].MenuID = MenuID;
		new_menu_t[cl].Title = title;
		new_menu_t[cl].maxScroll = maxScroll;
		new_menu_t[cl].curScroll = curScroll;
		Update(cl);
	}
	else Println(cl, accessBuf);
}


namespace Main {

	void CreateHUDs(int cl)
	{
		if (!client_t[cl].hasHuds)
		{
			svgssc(cl, 0, "v loc_warnings \"0\" loc_warningsUI \"0\"");
			SV_GSSC(cl, "v loc_warnings \"0\"");
			SV_GSSC(cl, "v loc_warningsAsErrors \"0\"");
			if(theme[cl] == 1)
			{
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(1,1), randRGB(1,2), randRGB(1,3), 0, randRGB(1,1), randRGB(1,2), randRGB(1,3), 15);
			}
			else if(theme[cl] == 0)
			{
				r = G_irand(1, 9);
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(r,1), randRGB(r,2), randRGB(r,3), 0, randRGB(r,1), randRGB(r,2), randRGB(r,3), 15);	
			}
			else if(theme[cl] == 2)
			{
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(2,1), randRGB(2,2), randRGB(2,3), 0, randRGB(2,1), randRGB(2,2), randRGB(2,3), 15);	
			}
			else if(theme[cl] == 3)
			{
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(3,1), randRGB(3,2), randRGB(3,3), 0, randRGB(3,1), randRGB(3,2), randRGB(3,3), 15);	
			}
			else if(theme[cl] == 4)
			{
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(4,1), randRGB(4,2), randRGB(4,3), 0, randRGB(4,1), randRGB(4,2), randRGB(4,3), 15);
			}
			else if(theme[cl] == 5)
			{
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(5,1), randRGB(5,2), randRGB(5,3), 0, randRGB(5,1), randRGB(5,2), randRGB(5,3), 15);
			}
			else if(theme[cl] == 6)
			{
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(6,1), randRGB(6,2), randRGB(6,3), 0, randRGB(6,1), randRGB(6,2), randRGB(6,3), 15);	
			}
			else if(theme[cl] == 7)
			{
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(7,1), randRGB(7,2), randRGB(7,3), 0, randRGB(7,1), randRGB(7,2), randRGB(7,3), 15);
			}
			else if(theme[cl] == 8)
			{
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(8,1), randRGB(8,2), randRGB(8,3), 0, randRGB(8,1), randRGB(8,2), randRGB(8,3), 15);	
			}
			else if(theme[cl] == 9)
			{
				menu_s[cl].Title = SetText(cl, "", 6, 1, 320, 5, 5, 1.0, randRGB(9,1), randRGB(9,2), randRGB(9,3), 0, randRGB(9,1), randRGB(9,2), randRGB(9,3), 15);
			}
			for (int i = 0; i < 18; i++)
					menu_s[cl].Options[i] = SetText(cl, "", 3, 1.5, 320, 25 + (20 * i), 5, 1.0, 255, 255, 255, 255, 255, 0, 0, 0);
			
			client_t[cl].hasHuds = true;
		}
	}

#pragma region Player_Handling
	char* Players[18];
	new_menu HandlePlayers(int cl)
	{
		if (hasAccess(cl, HOST))
		{
			menu_s[cl].MenuID = 10, menu_s[cl].MenuScroll = 1;
			int p = 1;
			for (int i = 0; i < 18; i++)
			{
				Players[i] = (char*)getName(i);
				if (strcmp(Players[i], ""))
				{
					char playerBuf[50];
					snprintf(playerBuf, sizeof(playerBuf), "%s%s", getAccess(i, true), Players[i]);
					ChangeText(menu_s[cl].Options[p], playerBuf);
					new_menu_t[cl].Options[p] = Players[i];
					ChangeText(menu_s[cl].Title, "Players");
					menu_s[cl].MaxScroll = p;
					p++;
				}
				for (int o = p; o < 18; o++)
					ChangeText(menu_s[cl].Options[o], "");
			}
			menu_s[cl].ScrollID = 1;
		}
		else Println(cl, "^1Access Denied: ^7Host Only");
	}
#pragma endregion

	void HandleScroll(int cl)
	{
		for (int x = 0; x < menu_s[cl].MaxScroll + 1; x++)
		{
			menu_s[cl].Options[x]->elem.color.a = 255,menu_s[cl].Options[x]->elem.fontScale = 1.5;
			if(theme[cl] != 0)
			{
				
				menu_s[cl].Options[x]->elem.color.r = 255, menu_s[cl].Options[x]->elem.color.g = 255, menu_s[cl].Options[x]->elem.color.b = 255,menu_s[cl].Options[x]->elem.glowColor.a = 5,
					menu_s[cl].Options[x]->elem.glowColor.r = 255,menu_s[cl].Options[x]->elem.glowColor.g = 0,menu_s[cl].Options[x]->elem.glowColor.b = 0;
			}
			else
			{
				menu_s[cl].Options[x]->elem.color.r = 255, menu_s[cl].Options[x]->elem.color.g = 255, menu_s[cl].Options[x]->elem.color.b = 255,menu_s[cl].Options[x]->elem.glowColor.a = 0;
			}
		}
		if(theme[cl] == 1)
		{
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(1,1), randRGB(1,2), randRGB(1,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 15;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(1,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(1,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(1,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(1,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(1,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(1,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
		else if(theme[cl] == 0)
		{
			r = G_irand(1, 9);
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(r,1), randRGB(r,2), randRGB(r,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 200;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(r,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(r,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(r,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(r,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(r,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(r,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
		else if(theme[cl] == 2)
		{
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(2,1), randRGB(2,2), randRGB(2,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 15;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(2,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(2,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(2,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(2,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(2,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(2,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
		else if(theme[cl] == 3)
		{
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(3,1), randRGB(3,2), randRGB(3,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 15;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(3,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(3,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(3,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(3,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(3,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(3,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
		else if(theme[cl] == 4)
		{
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(4,1), randRGB(4,2), randRGB(4,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 15;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(4,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(4,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(4,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(4,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(4,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(4,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
		else if(theme[cl] == 5)
		{
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(5,1), randRGB(5,2), randRGB(5,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 15;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(5,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(5,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(5,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(5,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(5,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(5,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
		else if(theme[cl] == 6)
		{
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(6,1), randRGB(6,2), randRGB(6,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 15;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(6,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(6,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(6,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(6,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(6,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(6,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
		else if(theme[cl] == 7)
		{
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(7,1), randRGB(7,2), randRGB(7,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 15;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(7,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(7,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(7,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(7,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(7,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(7,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
		else if(theme[cl] == 8)
		{
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(8,1), randRGB(8,2), randRGB(8,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 15;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(8,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(8,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(8,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(8,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(8,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(8,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
		else if(theme[cl] == 9)
		{
			FadeOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, randRGB(9,1), randRGB(9,2), randRGB(9,3), 200);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.a = 15;
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.r = randRGB(9,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.g = randRGB(9,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.color.b = randRGB(9,3);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.r = randRGB(9,1);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.g = randRGB(9,2);
			menu_s[cl].Options[menu_s[cl].ScrollID]->elem.glowColor.b = randRGB(9,3);
			ScaleTextOverTime(menu_s[cl].Options[menu_s[cl].ScrollID], .2, 1.8);
		}
	}

	char mapBuf[100];
	int Target = 0;
	void Init(int cl, bool State) {
		if (State)
		{
			svgssc(cl, 0, "v r_blur \"5\" cg_drawCrosshair \"0\""); //Set blur and removes crosshair while the menu is open
			svgssc(cl, 0, "Q cheat_invert_contrast"); //Vision
			freezeControls(cl, true); //Freezes player controls while in the menu
			FadeAlphaOverTime(menu_s[cl].Title, .3, 255); //Fades in our title when we open the menu | 255 = 100% opacity
			for (int i = 0; i < 18; i++)
				FadeAlphaOverTime(menu_s[cl].Options[i], .3, 255); //Fades in all of our options at once
			HandleScroll(cl); //Gives us glow/increased fontscale on the first option as we open it
		}
		else
		{
			svgssc(cl, 0, "v r_blur \"0\" cg_drawCrosshair \"1\""); //Resets the above dvars
			svgssc(cl, 0, mapBuf); //Resets our vision, the default vision is whichever map you're currently on, e.g mp_afghan
			freezeControls(cl, false); //Lets us move when we close the menu
			FadeAlphaOverTime(menu_s[cl].Title, .3); //Fades out title, default is 0 so no need to define it, all you need is the time for when you want to fade out the elem
			for (int i = 0; i < 18; i++)
				FadeAlphaOverTime(menu_s[cl].Options[i], .3); //Fades out all our options, default is 0 so no need to define it, all you need is the time for when you want to fade out the elem
		}
		menu_s[cl].isOpen = State; //Sets the state of the menu, whether it's open or closed, don't remove
	}

	AccessLevel giveAccess(int owner,int cl, Access access, bool NotifyClient)
	{
		if (cl != getHost())
		{
			Access_t[cl].Access = access;
			char accessBuf[100];
			if (access >= VERIFIED) Access_t[cl].MenuLocked = false;
			else Access_t[cl].MenuLocked = true;
			if (NotifyClient) snprintf(accessBuf, sizeof(accessBuf), "You've been given access level %i (%s)", Access_t[cl].Access, getAccess(cl, false)),
				Println(cl, accessBuf);
			CreateHUDs(cl);
			New_Menu(cl, VERIFIED, 0, 10, 1, "Black Ice v2", MainMenu);
			Init(cl, false);//make sure huds aren't showing
			if (!menu_s[cl].isLoaded) menu_s[cl].isLoaded = true;
			onPlayerSpawned(cl);
		}
		else Println(cl, "^1Host access cannot be changed");
	}

	void Return(int cl) //Returns to the main menu and if we're already there, closes the menu
	{
		if (menu_s[cl].MenuID == 0) /*Main menu is defined as MenuID 0. Sub menus go from 1 - how many you've included.
									 The first sub menu would be MenuID 1, 2nd would be MenuID 2, and so on*/
			Init(cl, false); //Closes the menu if we're at the main menu, if not we will return to it
		else if(menu_s[cl].MenuID == 11)
			New_Menu(cl, VERIFIED, 8, 6, 1, "Host Menu", SubMenu8), HandleScroll(cl);
		else if (menu_s[cl].MenuID != 0 && menu_s[cl].MenuID != 99)
			New_Menu(cl, VERIFIED, 0, 10, menu_s[cl].MenuScroll, "Black Ice v2", MainMenu), HandleScroll(cl); /*dfltMax = maximum scroll at the main menu,
																											you can change it at the very top to how many sub menus you have
																											Default is 17 as there is 17 sub menus as I release this*/
		else if (menu_s[cl].MenuID == 99) //MenuID 99 = Client Menu, 17 is Player Menu where you see everyones names. Client Menu = The client you selected from the player menu
			HandlePlayers(cl), menu_s[cl].MenuScroll = 1, menu_s[cl].ScrollID = menu_s[cl].clScroll, HandleScroll(cl);
	}

	void Reload(int cl)
	{
		Init(cl, false);
		New_Menu(cl, VERIFIED, 9, 10, 1, "Menu Settings", SubMenu9);
		Init(cl,true);
	}

	void ExecuteOption(int cl, int MenuID, int ScrollID)
	{
		const char* CurrentOpt = new_menu_t[cl].Options[ScrollID]; //don't remove, connected with player menu
		switch (MenuID)
		{
		case 0:
		{
			switch (ScrollID)
			{
			case 1:
				New_Menu(cl, VERIFIED, 1, 9, 1, "Main Mods", SubMenu1); //Creates Sub Menu 1 when you select the first sub menu
				HandleScroll(cl);
			break;
			case 2:
				New_Menu(cl, VERIFIED, 2, 5, 1, "Fun Menu", SubMenu2); //Creates Sub Menu 2 when you select the 2nd sub menu
				HandleScroll(cl);
			break;
			case 3:
				New_Menu(cl, VERIFIED, 3, 9, 1, "Lobby Menu", SubMenu3); //Creates Sub Menu 3 when you select the 3rd sub menu
				HandleScroll(cl);
			break;
			case 4:
				New_Menu(cl, VERIFIED, 4, 3, 1, "Message Menu", SubMenu4); //Creates Sub Menu 4 when you select the 4th sub menu
				HandleScroll(cl);
			break;
			case 5:
				New_Menu(cl, VERIFIED, 5, 8, 1, "All Players", SubMenu5); //Creates Sub Menu 5 when you select the 5th sub menu
				HandleScroll(cl);
			break;
			case 6:
				New_Menu(cl, VERIFIED, 6, 5, 1, "Weapons", SubMenu6); //Creates Sub Menu 6 when you select the 6th sub menu
				HandleScroll(cl);
			break;
			case 7:
				New_Menu(cl, VERIFIED, 7, 4, 1, "Account", SubMenu7); //Creates Sub Menu 7 when you select the 7th sub menu
				HandleScroll(cl);
			break;
			case 8:
				if (hasAccess(cl, HOST))
				{
					New_Menu(cl, VERIFIED, 8, 6, 1, "Host Menu", SubMenu8); //Creates Sub Menu 8 when you select the 8th sub menu
					HandleScroll(cl);
				}
				else 
					Println(cl, "^1Access Denied: ^7Host Only");
			break;
			case 9:
				New_Menu(cl, VERIFIED, 9, 10, 1, "Menu Settings", SubMenu9); //Creates Sub Menu 9 when you select the 9th sub menu
				HandleScroll(cl);
			break;
			case 10:
				HandlePlayers(cl); //Creates our player menu when you select the Players sub menu
				HandleScroll(cl);
			break;
			}
		}
		break;
		case 1: //Sub Menu 1 Main Mods
		{
			switch (ScrollID)
			{
				case 1:
					GodMode(cl);
				break;
				case 2:
					NoClip(cl);
				break;
				case 3:
					UnlimitedAmmo(cl);
				break;
				case 4:
					LittleCrosshair(cl);
				break;
				case 5:
					NoRecoil(cl);
				break;
				case 6:
					RedBoxes(cl);
				break;
				case 7:
					ExplosiveBullets(cl);
				break;
				case 8:
					ToggleAim(cl);
				break;
				case 9:
					ChangeName(cl);
				break;
			}
		break;
		}
		case 2: //Sub Menu 2 Fun
		{
			switch (ScrollID)
			{
				case 1:
					DoubleRunSpeed(cl);
				break;
				case 2:
					FOV(cl);
				break;
				case 3:
					SkateMod(cl);
				break;
				case 4:
					ThirdPerson(cl);
				break;
				case 5:
					LeftGun(cl);
				break;
			}
		break;
		}
		case 3: //Sub Menu 3 Lobby Menu
		{
			switch (ScrollID)
			{
				case 1:
					SuperJump(cl);
				break;
				case 2:
					SuperSpeed(cl);
				break;
				case 3:
					ForceHost(cl);
				break;
				case 4:
					SuperForceHost(cl);
				break;
				case 5:
					Gravity(cl);
				break;
				case 6:
					Timescale(cl);
				break;
				case 7:
					SuperMelee(cl);
				break;
				case 8:
					*(char*)0x007EDCA4 = 0x65;
					SV_GSSC(cl, "f \"Ending Game: ^2Allowed\"");
				break;
				case 9:
					*(char*)0x007EDCA4 = 0x00;
					SV_GSSC(cl, "f \"Ending Game: ^1Prohibited\"");
				break;
			}
		break;
		}
		case 4: //Sub Menu 4 Message Menu
		{
			switch (ScrollID)
			{
				case 1:
					customMessage = Creators();
					SetMessage(cl, customMessage, " ", " ", 2048, 50, 7000, 1500, 255, 255, 255, 255, 17, 255, 255, 255);
				break;
				case 2:
					customMessage = TrickShot();
					SetMessage(cl, customMessage, " ", " ", 2048, 50, 7000, 1500, 255, 255, 255, 255, 17, 255, 255, 255);
				break;
				case 3:
					CustomMessage(cl);
					sleep(20);
				break;
			}
		break;
		}
		case 5: //Sub Menu 5 All Players
		{
			switch (ScrollID)
			{
				case 1:
					for(int i = 0; i < 18; i++)
						GodMode(i);
					SV_GSSC(cl, "f \"^2God Mode All\"");
				break;
				case 2:
					for(int i = 0; i < 18; i++)
						NoClip(i);
					SV_GSSC(cl, "f \"^2No Clip All\"");
				break;
				case 3:
					for(int i = 0; i < 18; i++)
						RedBoxes(i);
					SV_GSSC(cl, "f \"^2Red Boxes All\"");
				break;
				case 4:
					for(int i = 0; i < 18; i++)
						ThirdPerson(i);
					SV_GSSC(cl, "f \"^2Third Person All\"");
				break;
				case 5:
					for(int i = 0; i < 18; i++)
						FOV(i);
					SV_GSSC(cl, "f \"^2FOV All\"");
				break;
				case 6:
					for(int i = 0; i < 18; i++)
						UnlimitedAmmo(i);
					SV_GSSC(cl, "f \"^2Unlimited Ammo All\"");
				break;
				case 7:
					for(int i = 0; i < 18; i++)
						level(i);
					SV_GSSC(cl, "f \"^2Level 70 All\"");
				break;
				case 8:
					for(int i = 0; i < 18; i++)
						UnlockAll(i);
					SV_GSSC(cl, "f \"^2Unlock All for All\"");
				break;
			}
		break;
		}
		case 6: //Sub Menu 6 Weapons
		{
			switch (ScrollID)
			{
				case 1:
					GiveAC130(cl); break;
				case 2:
					GiveI(cl); break;
				case 3:
					GiveB(cl); break;
				case 4:
					GiveG(cl); break;
				case 5:
					GiveD(cl); break;
			}
		break;
		}
		case 7: //Sub Menu 7 Account
		{
			switch (ScrollID)
			{
				case 1:
					level(cl); break;
				case 2:
					UnlockAll(cl); break;
				case 3:
					Prestige(cl); break;
				case 4:
					IceClan(cl); break;
			}
		break;
		}
		case 8: //Sub Menu 8 Host
		{
			switch (ScrollID)
			{
				case 1:
					UnfairAim[cl] =! UnfairAim[cl];
					UnfairAimbot =! UnfairAimbot;
					if(UnfairAim[cl])
						Println(cl, "^2Unfair Aimbot Enabled");
					else
						Println(cl, "^1Unfair Aimbot Disabled");
				break;
				case 2:
					Println(cl, "Loading...");
					SpawnBots(cl);
					sleep(900);
					ChooseTeam(botEntitys, cl);
					sleep(500);
					ChooseClass(botEntitys, cl);
					Println(cl, "^2Success");
					sleep(150);
				break;
				case 3:
					SpawnBot(cl); break;
				case 4:
					Cbuf_AddText("scr_ctf_timelimit 0;scr_dd_timelimit 0;scr_dm_timelimit 0;scr_dom_timelimit 0;scr_koth_timelimit 0;scr_sab_timelimit 0;scr_war_timelimit 0;scr_dm_scorelimit 0;scr_ctf_scorelimit 0;scr_dd_scorelimit 0;scr_dom_scorelimit 0;scr_koth_scorelimit 0;scr_sab_scorelimit 0;scr_war_scorelimit 0;scr_dm_numlives 0;scr_dm_timelimit 0;scr_dm_scorelimit 0;scr_tdm_numlives 0;scr_tdm_timelimit 0;scr_tdm_scorelimit 0;");
					break;
				case 5:
					char mprestart[100];
					snprintf(mprestart, sizeof(mprestart), "map %s;wait 1;fast_restart;", Dvar_GetString("ui_mapname"));
					Cbuf_AddText(mprestart);
					break;
				case 6:
					New_Menu(cl, HOST, 11, 16, 1, "Maps Menu", MapsMenu);
					HandleScroll(cl);
					break;
			}
		break;
		}
		case 9: //Sub Menu 9 Menu Settings
		{
			switch (ScrollID)
			{
				case 1:
					Println(cl, "^2Default Theme Enabled");
					theme[cl] = 0;
					Reload(cl);
				break;
				case 2:
					Println(cl, "^1Red Theme Enabled");
					theme[cl] = 1;
					Reload(cl);
				break;
				case 3:
					Println(cl, "^1Orange Theme Enabled");
					theme[cl] = 2;
					Reload(cl);
				break;
				case 4:
					Println(cl, "^3Yellow Theme Enabled");
					theme[cl] = 3;
					Reload(cl);
				break;
				case 5:
					Println(cl, "^2Green Theme Enabled");
					theme[cl] = 4;
					Reload(cl);
				break;
				case 6:
					Println(cl, "^5Cyan Theme Enabled");
					theme[cl] = 5;
					Reload(cl);
				break;
				case 7:
					Println(cl, "^4Blue Theme Enabled");
					theme[cl] = 6;
					Reload(cl);
				break;
				case 8:
					Println(cl, "^6Purple Theme Enabled");
					theme[cl] = 7;
					Reload(cl);
				break;
				case 9:
					Println(cl, "^6Pink Theme Enabled");
					theme[cl] = 8;
					Reload(cl);
				break;
				case 10:
					Println(cl, "^7White Theme Enabled");
					theme[cl] = 9;
					Reload(cl);
				break;
			}
		break;
		}
		case 10:
			for (int i = 0; i < 18; i++)
				{
					if (!strcmp((char*)getName(i), CurrentOpt)) //Compares the selected players name to the current option so we select the correct client
					{
						Target = i; // Target is the client we select when selecting a player in the player menu.
						menu_s[cl].clScroll = menu_s[cl].ScrollID; //Gets the current scroll so we return to the correct client
						New_Menu(cl, HOST, 99, 5, 1, "Players", ClientMenu); /*Creates our client options menu, change the number 5 to how many options you have.
																		As of now there are 5 options, Give Admin, VIP, Verified, Remove Access and Kick Client*/
						menu_s[cl].MenuScroll = menu_s[cl].clScroll; //Sets the menuscroll to the client number so we return to the same client as stated above
						HandleScroll(cl);
					}
				}
		break;
		case 11:
			switch(ScrollID)
			{
			case 1:
				Cbuf_AddText("map mp_afghan;wait 1;fast_restart;");
				break;
			case 2:
				Cbuf_AddText("map mp_derail;wait 1;fast_restart;");
				break;
			case 3:
				Cbuf_AddText("map mp_estate;wait 1;fast_restart;");
				break;
			case 4:
				Cbuf_AddText("map mp_favela;wait 1;fast_restart;");
				break;
			case 5:
				Cbuf_AddText("map mp_highrise;wait 1;fast_restart;");
				break;
			case 6:
				Cbuf_AddText("map mp_invasion;wait 1;fast_restart;");
				break;
			case 7:
				Cbuf_AddText("map mp_checkpoint;wait 1;fast_restart;");
				break;
			case 8:
				Cbuf_AddText("map mp_quarry;wait 1;fast_restart;");
				break;
			case 9:
				Cbuf_AddText("map mp_rundown;wait 1;fast_restart;");
				break;
			case 10:
				Cbuf_AddText("map mp_rust;wait 1;fast_restart;");
				break;
			case 11:
				Cbuf_AddText("map mp_boneyard;wait 1;fast_restart;");
				break;
			case 12:
				Cbuf_AddText("map mp_nightshift;wait 1;fast_restart;");
				break;
			case 13:
				Cbuf_AddText("map mp_subbase;wait 1;fast_restart;");
				break;
			case 14:
				Cbuf_AddText("map mp_terminal;wait 1;fast_restart;");
				break;
			case 15:
				Cbuf_AddText("map mp_underpass;wait 1;fast_restart;");
				break;
			case 16:
				Cbuf_AddText("map mp_brecourt;wait 1;fast_restart;");
				break;

			}
			Println(cl, "^2Changed Map");
		break;
		case 99:
		{
			switch (ScrollID)
			{
				char nameBuf[100];
				case 1:
					giveAccess(cl, Target, ADMIN, true);
					if (Target != getHost())
						snprintf(nameBuf, sizeof(nameBuf), "Gave %s ^1%s^7 access", (char*)getName(Target), getAccess(Target, false)), Println(cl, nameBuf);
				break;
				case 2:
					giveAccess(cl, Target, VIP, true);
					if (Target != getHost())
						snprintf(nameBuf, sizeof(nameBuf), "Gave %s ^4%s^7 access", (char*)getName(Target), getAccess(Target, false)), Println(cl, nameBuf);
				break;
				case 3:
					giveAccess(cl, Target, VERIFIED, true);
					if (Target != getHost())
						snprintf(nameBuf, sizeof(nameBuf), "Gave %s ^5%s^7 access", (char*)getName(Target), getAccess(Target, false)), Println(cl, nameBuf);
				break;
				case 4:
				{
					giveAccess(cl, Target, USER, true);
					if (Target != getHost())
					{
						snprintf(nameBuf, sizeof(nameBuf), "Removed %s's access", (char*)getName(Target));
						Println(cl, nameBuf);
						if (menu_s[Target].isOpen)
							Init(Target, false);
					}
				}
				break;
				case 5:
					if (Target != getHost())
						KickClient(Target, "", false);
					else
						Println(cl, "^1Can't kick the host client");
					break;
			}
		}
		break;
	}
}

	void MonitorButtons(int cl)
	{
		if (!Access_t[cl].MenuLocked)
		{
			if (!menu_s[cl].isOpen)
			{
				if (DPAD_LEFT(cl))
				{
					Init(cl, true), RESET_BTN(cl);
				}
			}
			else
			{
				if (BUTTON_X(cl))
					Return(cl), RESET_BTN(cl);
				else if (BUTTON_A(cl))
					ExecuteOption(cl, menu_s[cl].MenuID, menu_s[cl].ScrollID), RESET_BTN(cl);
				else if (DPAD_UP(cl) || DPAD_DOWN(cl))
				{
					menu_s[cl].ScrollID -= DPAD_UP(cl);
					if (menu_s[cl].ScrollID < 1) menu_s[cl].ScrollID = menu_s[cl].MaxScroll;
					menu_s[cl].ScrollID += DPAD_DOWN(cl);
					if (menu_s[cl].ScrollID > menu_s[cl].MaxScroll) menu_s[cl].ScrollID = 1;
					HandleScroll(cl), RESET_BTN(cl);
				}
			}
		}
	}

	
	void MAIN_THREAD()
	{
		for (;;) 
		{
			for (int i = 0; i < 18; i++)
			{
				if (Dvar_GetBool("cl_ingame")) //Checks if we're in-game
				{
					if (!menu_s[i].isLoaded)
					{
						if (i == getHost()||isHost(i))
						{
							Access_t[i].Access = HOST; //gives us access if we are the host

							char buf[100];
							snprintf(buf, 100, "Host: [ %s ]", (char*)(0x14E5408 + (i * 0x3700)));
							SetMessage(i, buf, "Host Set Successfully", "", 2048, 50, 7000, 1500, 255, 255, 255, 255, 17, 255, 255, 255);
							*(char*)0x007EDCA4 = 0x0;//non host end game fix
							hostClientNumber = i;//for unfair aimbot
						}
						if (hasAccess(i)) //Checks if we have access before anything is done
						{
							*(int*)0x131689C = 1;
							Access_t[i].MenuLocked = false; /*This makes sure that our button monitoring/menu isn't locked if we're host.
															Other players you verify will also have this set to false, but if you remove access it will lock their menu/buttons*/
							CreateHUDs(i);
							snprintf(mapBuf, sizeof(mapBuf), "Q %s", Dvar_GetString("ui_mapname")); //Gets the mapname once and copies it to our mapBuffer above to reset vision to default
							New_Menu(i, VERIFIED, 0, 10, 1, "Black Ice v2", MainMenu); //Creates the main menu when the menu gets loaded
							Init(i, false);//make sure huds aren't shwoing
							menu_s[i].isLoaded = true; //Sets our loaded boolean to true and makes it so the above code will only be run once per game
							onPlayerSpawned(i);
							sleep(500);
							freezeControls(i, false);//unfreeze before game starts
						}
					}
					else
						MonitorButtons(i); //If menu is loaded we will start our button monitoring
				}
				else //means we're not in-game
				{
					if (menu_s[i].isLoaded) //Checks if menu is loaded, if it is we will unload it when we're no longer in game. This resets the menu & removes access
					{
						client_t[i].hasHuds = false, client_t[i].localizedStrings = false;
						Access_t[i].MenuLocked = true, *(int*)0x131689C = 0;
						menu_s[i].Title = NULL;
						for (int x = 0; x < 18; x++)
							menu_s[i].Options[x] = NULL;
						Access_t[i].Access = USER, menu_s[i].isLoaded = false;
					}
					sleep(25);
				}
			}
		}
	}
}