//YGO!tDoD_Randomizer.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

//names - A - Zera the Mant
//names - AA - Tri-horned Dragon
//names - AAA - Cosmo Queen

_Bool DEBUG = false;

void randomize_tier_people_duel_machine_tier(FILE* fp)
{
	
	if(DEBUG)
		printf("randomize_tier_people \n");
	unsigned char people_list[] = {
		//tier 1
			0x1A, //Shimon
			0x06, //Grandpa
			0x03, //Yugi
		//tier 2
			0x04, //Tea
			0x05, //Tristan
			0x02, //Joey
		//tier 3
			0x07, //Bakura
			0x19, //Shadi
			0x00, //Yami Yugi
		//tier 4
			0x0E, //Weevil
			0x0D, //Rex Raptor
			0x0C, //Mako
		//tier 5
			0x0F, //Bonz
			0x0B, //Bandit Keith
			0x09, //Pegasus
		//tier 6
			0x0A, //Mai
			0x03, //Yugi
			0x01, //Kaiba
		//tier 7
			0x11, //Rare Hunter
			0x12, //Arkana
			0x14, //Strings
		//tier 8
			0x10, //Espa Roba
			0x13, //Lumis & Umbra
			0x17, //Marik
		//tier 9
			0x15, //Ishizu
			0x16, //Odion
			0x18, //Yami Marik
		//tier 10
			0x0A, //Mai
			0x02, //Joey
			0x17, //Marik
		//tier 11
			0x15, //Ishizu
			0x16, //Odion
			0x08, //Yami Bakura
		//tier 12
			0x18, //Yami Marik
			0x01, //Kaiba
			0x00, //Yami Yugi
		//tier 13
			0x11, //Rare Hunter
			0x11, //Rare Hunter
			0x11, //Rare Hunter
		//tier 14
			0x18, //Yami Marik
			0x08, //Yami Bakura
			0x00, //Yami Yugi
		//tier 15
			0x1B, //Duel Machine
			0x1B, //Duel Machine
			0x1B, //Duel Machine
	};
	
	int z;
	int name_to_fight_start_address = 0x4C8B30;
	int picture_address = 0x496BA0; 
	int randVal;
	int SIZE = 1;
	unsigned char buffer[SIZE];
	unsigned char newByte = 0xFF;
	
	//initialize
	if(DEBUG)
		printf("initialize \n");
	for(int i = 0; i < 3*15; i++)
	{
		fseek(fp,name_to_fight_start_address+(i*8),SEEK_SET);
		fwrite(&newByte,sizeof(newByte),1,fp);
		fseek(fp,picture_address+(i*8),SEEK_SET);
		fwrite(&newByte,sizeof(newByte),1,fp);
	}
	if(DEBUG)
		printf("initialization complete \n");
		
	randVal = (rand() % 15);
	if(DEBUG)
		printf("Duel Machines on tier %d \n",randVal+1);
	int offset = randVal * 0x18;
	
	newByte = 0x1B;
	for(int i = 0; i < 3; i++)
	{
		fseek(fp,name_to_fight_start_address+offset+(i*8),SEEK_SET);
		fwrite(&newByte,sizeof(newByte),1,fp);
		fseek(fp,picture_address+offset+(i*8),SEEK_SET);
		fwrite(&newByte,sizeof(newByte),1,fp);
	}
	if(DEBUG)
		printf("wrote duel machine tier \n");
	people_list[(3*15)-1] = 0xFF;
	people_list[(3*15)-2] = 0xFF;
	people_list[(3*15)-3] = 0xFF;
	if(DEBUG)
		printf("starting other tiers \n");
	for(int i = 0; i < 3*15; i++)
	{
		if(DEBUG)
			printf("i: %d\n",i);
		buffer[0] = 0x00;
		fseek(fp, name_to_fight_start_address+(i*8), SEEK_SET);
		if(DEBUG)
			printf("seek to 0x%x\n",name_to_fight_start_address+(i*8));
		if (fread(buffer, sizeof(buffer), 1, fp) != 1) {
			if(DEBUG) printf("Failed to read from file at position: 0x%x\n", name_to_fight_start_address+(i*8));
			continue;
		}
		if(DEBUG) printf("buffer[0]: 0x%02X\n", buffer[0]);
		//printf("%c \n",buffer[0]);
		if(buffer[0] != 0x1B) 
		{
			if(DEBUG)
				printf("writing character \n");
			do
			{
				randVal = (rand() % (3 * 15));
			}while(people_list[randVal] == 0xFF);
			if(DEBUG)
				printf("chose 0x%02X\n",people_list[randVal]);
			fseek(fp, name_to_fight_start_address+(i*8), SEEK_SET);
			fwrite(&people_list[randVal],sizeof(people_list[randVal]),1,fp); //the file write isn't happening?
			fseek(fp, picture_address+(i*8),SEEK_SET);
			fwrite(&people_list[randVal],sizeof(people_list[randVal]),1,fp);
			people_list[randVal] = 0xFF;
			if(DEBUG)
				printf("finished writing character\n");
		}
		else
		{
			//do nothing
			if(DEBUG)
				printf("Skipped for duel machine\n");
		}
	}
}

void randomize_tier_people_no_duel_machine_tier(FILE* fp)
{	
	if(DEBUG)
		printf("randomize_tier_people \n");
	unsigned char people_list[] = {
		//tier 1
			0x1A, //Shimon
			0x06, //Grandpa
			0x03, //Yugi
		//tier 2
			0x04, //Tea
			0x05, //Tristan
			0x02, //Joey
		//tier 3
			0x07, //Bakura
			0x19, //Shadi
			0x00, //Yami Yugi
		//tier 4
			0x0E, //Weevil
			0x0D, //Rex Raptor
			0x0C, //Mako
		//tier 5
			0x0F, //Bonz
			0x0B, //Bandit Keith
			0x09, //Pegasus
		//tier 6
			0x0A, //Mai
			0x03, //Yugi
			0x01, //Kaiba
		//tier 7
			0x11, //Rare Hunter
			0x12, //Arkana
			0x14, //Strings
		//tier 8
			0x10, //Espa Roba
			0x13, //Lumis & Umbra
			0x17, //Marik
		//tier 9
			0x15, //Ishizu
			0x16, //Odion
			0x18, //Yami Marik
		//tier 10
			0x0A, //Mai
			0x02, //Joey
			0x17, //Marik
		//tier 11
			0x15, //Ishizu
			0x16, //Odion
			0x08, //Yami Bakura
		//tier 12
			0x18, //Yami Marik
			0x01, //Kaiba
			0x00, //Yami Yugi
		//tier 13
			0x11, //Rare Hunter
			0x11, //Rare Hunter
			0x11, //Rare Hunter
		//tier 14
			0x18, //Yami Marik
			0x08, //Yami Bakura
			0x00, //Yami Yugi
		//tier 15
			0x1B, //Duel Machine
			0x1B, //Duel Machine
			0x1B, //Duel Machine
	};
	
	int z;
	int name_to_fight_start_address = 0x4C8B30;
	int picture_address = 0x496BA0; 
	int randVal;
	int SIZE = 1;
	unsigned char buffer[SIZE];
	unsigned char newByte = 0xFF;
	
	char used_pos[] = {
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
		'N','N','N',
	};
	
	//choose 3 positions for the duel machines that have to be %3 == 1, %3 == 2, %3 == 0
	do //Duel Machine 3
	{
		randVal = rand() % (3*15);
	}while(randVal % 3 != 0);
	fseek(fp,name_to_fight_start_address+(randVal*8),SEEK_SET);
	fwrite(&people_list[(3*15)-1],sizeof(people_list[(3*15)-1]),1,fp);
	fseek(fp,picture_address+(randVal*8),SEEK_SET);
	fwrite(&people_list[(3*15)-1],sizeof(people_list[(3*15)-1]),1,fp);
	used_pos[randVal] = 'Y';
	
	do //Duel Machine 2
	{
		randVal = rand() % (3*15);
	}while(randVal % 3 != 2);
	fseek(fp,name_to_fight_start_address+(randVal*8),SEEK_SET);
	fwrite(&people_list[(3*15)-2],sizeof(people_list[(3*15)-2]),1,fp);
	fseek(fp,picture_address+(randVal*8),SEEK_SET);
	fwrite(&people_list[(3*15)-2],sizeof(people_list[(3*15)-2]),1,fp);
	used_pos[randVal] = 'Y';
	
	do //Duel Machine 1
	{
		randVal = rand() % (3*15);
	}while(randVal % 3 != 1);
	fseek(fp,name_to_fight_start_address+(randVal*8),SEEK_SET);
	fwrite(&people_list[(3*15)-3],sizeof(people_list[(3*15)-3]),1,fp);
	fseek(fp,picture_address+(randVal*8),SEEK_SET);
	fwrite(&people_list[(3*15)-3],sizeof(people_list[(3*15)-3]),1,fp);
	used_pos[randVal] = 'Y';
	
	//choose places for the rest of the characters
	for(int i = 0; i < (3*14); i++)
	{
		do
		{
			randVal = rand() % (3*15);
		}while(used_pos[randVal] == 'Y');
		fseek(fp,name_to_fight_start_address+(randVal*8),SEEK_SET);
		fwrite(&people_list[i],sizeof(people_list[i]),1,fp);
		fseek(fp,picture_address+(randVal*8),SEEK_SET);
		fwrite(&people_list[i],sizeof(people_list[i]),1,fp);
		used_pos[randVal] = 'Y';
	}
}


void randomize_tier_LP(FILE* fp)
{
	if(DEBUG)
		printf("randomize_tier_LP \n");
	int lp_values[] = {
		//tier 1
			0x07D0, //shimon 2000
			0x07D0, //grandpa 2000
			0x0BB8, //yugi 3000
		//tier 2
			0x07D0, //tea 2000
			0x0BB8, //tristan 3000
			0x0BB8, //joey 3000
		//tier 3
			0x0BB8, //bakura 3000
			0x0BB8, //shadi 3000
			0x0FA0, //yami yugi 4000
		//tier 4
			0x0FA0, //Weevil 4000
			0x0FA0, //Rex Raptor 4000
			0x0FA0, //Mako 4000
		//tier 5
			0x0FA0, //bonz 4000
			0x1388, //bandit keith 5000
			0x1770, //pegasus 6000
		//tier 6
			0x1388, //mai 5000
			0x1770, //yugi 6000
			0x1770, //kaiba 6000
		//tier 7
			0x0FA0, //rare hunter 4000
			0x0FA0, //arkana 4000
			0x0FA0, //strings 4000
		//tier 8
			0x0BB8, //espa roba 3000
			0x0FA0, //lumis & umbra 4000
			0x1770, //marik 6000
		//tier 9
			0x0FA0, //ishizu 4000
			0x1388, //odion 5000
			0x1F40, //yami marik 8000
		//tier 10
			0x0BB8, //mai 3000
			0x0BB8, //joey 3000
			0x1770, //marik 6000
		//tier 11
			0x0FA0, //ishizu 4000
			0x0FA0, //odion 4000
			0x1770, //yami bakura 6000
		//tier 12
			0x1F40, //yami marik 8000
			0x1F40, //kaiba 8000
			0x1F40, //yami yugi 8000
		//tier 13
			0x0FA0, //rare hunter 4000
			0x0FA0, //rare hunter 4000
			0x0FA0, //rare hunter 4000
		//tier 14
			0x0FA0, //yami marik 4000
			0x0FA0, //yami bakura 4000
			0x0FA0, //yami yugi 4000
		//tier 15
			0x0FA0, //Duel Machine 4000
			0x0FA0, //Duel Machine 4000
			0x0FA0, //Duel Machine 4000
	};
	
	int randVal;
	int name_to_fight_start_address = 0x4C8B30;
	
	for(int i = 0; i < 3*15; i++)
	{
		do
		{
			randVal = rand() % (3*15);
		}while(lp_values[randVal] == 0xFFFF);
		fseek(fp,((name_to_fight_start_address+4)+(i*8)),SEEK_SET);
		fwrite(&lp_values[randVal],sizeof(lp_values[randVal]),1,fp);
		lp_values[randVal] = 0xFFFF;
	}
}

void randomize_your_tier_LP(FILE* fp)
{
	if(DEBUG)
		printf("randomize_your_tier_LP\n");
	//tier_1_lp = 0x4C8AF0,
	int tier_lp[] = {
		6000, //1
		7000, //2
		8000, //3
		10000, //4
		11000, //5
		12000, //6
		8000, //7
		10000, //8
		12000, //9
		8000, //10
		8000, //11
		14000, //12
		6000, //13
		6000, //14
		6000, //15
	};
	
	int randVal;
	
	for(int i = 0; i < 15; i++)
	{
		do
		{
			randVal = rand() % 15;
		}while(tier_lp[randVal] == -1);
		fseek(fp,0x4C8AF0+(i*4),SEEK_SET);
		fwrite(&tier_lp[randVal],sizeof(tier_lp[randVal]),1,fp);
		tier_lp[randVal] = -1;
	}
}

//start of monster name text = 0x5F90A4
int messages_text = 0x005F2E59; //start of messages
int card_names_text = 0x005F90A4; //Start of Card Names
int card_text = 0x005FD62C; //Start of Card Text
int phase_names = 0x620127; //Start of Phases
int card_types_text = 0x6201EC; //Start of Types
int card_attribute_text = 0x6202A8; //Start of Attributes
int people_names_text = 0x620880; //Start of People Names
int deck_names_text = 0x620AA7; //?Start of Deck Names?Types?
int people_names_text_2 = 0x5F2128; //Start of People Names

void randomize_starting_deck(FILE* fp)
{
	//currently you cannot change cards in deck 1.
	printf("\n\nDO NOT MODIFY DECK 1 IN THE GAME!!!\n\n");
	//Choose between the starting decks, or the character decks.

/*
Starting Deck - Zera the Mant - 0x756010 / side deck - 0x756100
EF 01 19 01 C5 00 1B 00 41 00 30 02 E2 01 00 00 00 00 3F 01 60 00 50 00 4A 00 BA 01 0B 02 00 00 00 00 00 00 00 00 40 01 94 03 A4 01 7D 00 4E 00 DC 00 41 02 F4 00 1C 01 62 02 00 00 0D 00 46 00 8F 01 E7 03 1B 01 E7 00 93 01 22 00 00 00 26 01 45 03 52 01 FC 02 F1 02 00 00 E6 01 00 00 87 02 86 02 5D 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 47 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 8B 02 99 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Starting Deck - Cosmo Queen - 0x752810 / side deck - 0x752900
9F 02 04 02 16 01 FD 00 02 00 AF 00 D8 01 39 01 00 00 00 00 93 00 86 00 E4 00 48 02 B1 00 11 01 20 02 20 01 87 00 27 01 22 01 EC 00 35 00 31 00 5C 01 8A 01 B9 01 C9 00 17 01 7F 01 64 01 A0 00 DC 01 82 01 9F 01 7D 01 00 00 00 00 00 00 00 00 DB 02 E2 02 FC 02 F1 02 00 00 44 01 87 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 47 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 96 02 A9 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Starting Deck - Tri-horned Dragon - 0x74F010 / side deck - 0x74F100
9C 02 D0 02 87 01 1A 00 7A 00 77 02 29 00 55 01 19 00 19 00 D1 00 1D 02 E9 03 BD 00 0B 01 D4 00 36 00 BC 02 C0 00 1E 01 75 01 75 01 00 00 06 00 F3 00 A6 00 95 00 5F 02 F1 00 5C 02 00 00 00 00 00 00 9F 01 00 00 00 00 4D 00 0E 01 2D 02 00 00 F1 02 FC 02 46 03 00 00 00 00 00 00 08 03 87 02 1F 03 36 04 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 47 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00 8A 02 98 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Duel Computer 1
--------------------------

Mystic Tomato x2
Sangan
Cyber Jar
Morphing Jar
Mushroom Man x2
Man Eating Plant
Stuffed Animal x2
Eyearmor x2
Millennium Shield x2
Yashinoki
Snakeyashi x2
Laughing Flower x2
Psychic Kappa x2
Haniwa x2
Dark Plant
Firegrass
Barrel Lily
Ancient Tree of Enlightenment x2
Bean Soldier
Man Eater

Snatch Steal
Delinquent Duo
Pot of Greed
Graceful Charity
Card Destruction

Magic Jammer x2
Jar of Greed x2
Solemn Wishes
Negate Attack x2
Gamble x2
Magic Thorn
Just Desserts
Torrential Tribute
Backup Soldier


Duel Computer 2
--------------------------

Dragon Zombie x2
Armored Zombie x2
Giant Soldier of Stone x2
Twin Long Rods #2 x2
Man Eater Bug x2
The Judgement Hand x2
Monsturtle
Magician of Faith x2
Wetha x2
Trakadon x2
The Melting Red Shadow
Turu-Purun
Frog the Jam
Change Slime
Kappa Avenger
Aqua Snake
Zarigun
Dorover
Ice Water x2
Toad Master
Liquid Beast x2
Kanikabuto
Turtle Raccoon

Axe of Despair
Mage Power
United We Stand
Harpie's Feather Duster
Mystical Space Typhoon
Dark Hole
Raigeki

Gravity Bind x3
Gryphon Wing
Ring of Destruction
Magic Jammer
Solemn Wishes


Duel Computer 3
--------------------------

Vorse Raider x2
Slate Warrior x2
La Jinn the Mystical Genie of the Lamp x2
Grand Tiki Elder x2
Dragon Statue x2
Hyo
M-Warrior #1
M-Warrior #2 x2
Monster Egg
Stuffed Animal
Hero of the East
Unknown Warrior of Fiend
Supporter in the Shadows
Kagemusha of the Blue Flame
Masaki the Legendary Swordsman
Rhaimundos of the Red Sword
Fiend Sword
Moon Envoy
Kageningen
Eyearmor x2
Dark Magician
Summoned Skull x2
Dark Magician Girl
Magician of Black Chaos x2
Jinzo

Dark Magic Ritual
Harpie's Feather Duster
Mystical Space Typhoon
Tribute to the Doomed
Premature Burial
Heavy Storm

Trap Hole
Solemn Wishes
Jar of Greed x2
Negate Attack
Just Desserts
Magic Jammer
Seven Tools of the Bandit
Ring of Destruction


Shimon
--------------------------

Darkworld Thorns
Abyss Flower
Dark Plant
Barrel Rock x2
Slate Warrior
Mystic Tomato x2
Firegrass x2
Dice Armadiller x3
Barrel Lily x2
Stone Ghost
Ancient Jar
Fire Eye
Wings of Wicked Flame x2
Tentacle Plant
Minomushi Warrior
Bean Soldier
Laughing Flower
Destroyer Golem
Penguin Soldier
Sangan
Prisman
Man Eating Plant
Flame Viper
Fireyarou
The Statue of Easter Island x2
Hinotama Soul
Haniwa
Abyss Flower
Snakeyashi
Living Vase

Upstart Goblin
Raigeki

Jar of Greed x3
Backup Soldier
Trap Hole x2
Torrential Tribute
Negate Attack
Fairy Box
Call of the Haunted


Grandpa
--------------------------

Exodia the Forbidden One
Right Arm of the Forbidden One
Left Arm of the Forbidden One
Right Leg of the Forbidden One
Left Leg of the Forbidden One
Blue Eyes White Dragon
Penguin Soldier x2
White Magical Hat
Neo the Magic Swordsman
Mystic Tomato
Sangan
Boo Koo
Phantom Dewan
The Bewitching Phantom Thief
Celtic Guardian x2
Sorcerer of the Doomed x2
Aqua Madoor
Genin
Nemuriko
Akakieisu
Flame Manipulator
Djinn the Watcher of the Wind
Hurricail
Lucky Trinket
Tao the Chanter
Ancient Sorcerer

Graceful Charity
Monster Reborn
Pot of Greed
Change of Heart

Trap Hole x2
Magic Jammer x2
Negate Attack
Torrential Tribute x2
Backup Soldier x2
Call of the Haunted
Jar of Greed x2
Mirror Force


Yugi
--------------------------

Dark Magician x3
Gaia the Fierce Knight
Curse of Dragon
Beaver Warrior
Koumori Dragon
Celtic Guardian
Feral Imp
Horn Imp
Blackland Fire Dragon
Winged Dragon, Guardian of the Fortress #1 x3
Giant Soldier of Stone x3
Mystical Elf x3
Silver Fang x2
Griffore
Gazelle the King of Mythical Beasts x3
Summoned Skull
Alpha the Magnet Warrior
Beta the Magnet Warrior
Gamma the Magnet Warrior
Sangan
Great White
Flame Cerberus

Polymerization
Change of Heart
Harpie's Feather Duster
Monster Reborn
Swords of Revealing Light
Dark Hole

Mirror Force
Magic Cylinder
Trap Hole
Royal Decree
Ring of Destruction
Negate Attack

Gaia the Dragon Champion


Tea
--------------------------

Dunames Dark Witch
The Forgiving Maiden x3
Marie the Fallen One x3
Fire Princess x3
Spirit of the Harp
Kaminarikozou
Vishwar Randi x2
Arlownay x2
Bolt Escargot
Nekogal #2 x2
Tripwire Beast
Dryad
Fairy of the Fountain
Eldeen x2
Lunar Queen Elzaim x2
Amazon of the Seas x2
Water Magician
Ancient Elf
Fairy's Gift
Lala Li-oon
Kanan the Swordmistress
Waterdragon Fairy
Fairywitch
Protector of the Throne
Water Girl x2
Nekogal #1
Gemini Elf
Water Element
Enchanting Mermaid
Maiden of the Moonlight

United We Stand
Mage Power
Fusion Sage
Polymerization x3

Magic Jammer
Numinous Healer
Trap Hole
Solemn Wishes
Aqua Chorus

St. Joan x3


Tristan
--------------------------

Goblin Attack Force x3
Giant Soldier of Stone x2
Muka Muka x2
Dokurorider
Unknown Warrior of Fiend x2
Meotoko x2
M-Warrior #1
M-Warrior #2 x2
Dark Gray x2
Armored Rat
Monster Egg
Kagemusha of the Blue Flame
Dragon Statue
Skull Stalker x2
Eyearmor x2
Sleeping Lion x2
Synchar
Fiend Sword
Moon Envoy
Wolf Axwielder
Wood Clown
Solitude
Gate Deeg
Armaill x2
Battle Ox
Prevent Rat
Obese Marmot of Nefariousness
Hero of the East
Hyo
Ogre of the Black Shadow
Mountain Warrior
Guardian of the Labyrinth
Stuffed Animal

Megamorph
Revival of Dokurorider
Axe of Despair
Black Pendant
Horn of the Unicorn

Enchanted Javelin
Negate Attack


Joey
--------------------------

Panther Warrior x2
Zombyra the Dark x2
Axe Raider
Kojikocy
Armored Lizard
Alligator's Sword x2
Baby Dragon x2
Time Wizard x2
Meteor Dragon
Red Eyes Black Dragon x2
Summoned Skull x2
The Legendary Fisherman
Zanki
Wolf
Battle Warrior
Swordsman of Landstar
Tiger Axe x2
Battle Steer
Ansatsu
Meteor Dragon x2
Beautiful Beast Trainer
Jinzo

Monster Reborn
Fusion Sage x2
Polymerization x2
United We Stand
Mage Power
Axe of Despair x2
Change of Heart
Snatch Steal
Graceful Charity

Mirror Force

Meteor B. Dragon
Black Skull Dragon x2
Alligator's Sword Dragon x2
Thousand Dragon x2


Bakura
--------------------------

Maha Vailo x3
Whiptail Crow x2
Man-Eating Treasure Chest
Baron of the Fiend Sword
Ancient Brain
Happy Lover
Wicked Mirror
Wretched Ghost of the Attic
Claw Reacher
Fungi of the Musk
Madjinn Gunn
That Which Feeds on Life
Job-Change Mirror
Gorgon Egg
Terra the Terrible
Gross Ghost of Fled Dreams
Headless Knight
The Portrait's Secret
Dark Titan of Terror x3
Bio Plant x2
Dark Prisoner
Midnight Fiend
Mystic Clown
Invader from Another Dimension
Mystical Capture Chain
Embryonic Beast
Trial of Nightmare x2
Lord of the Lamp
Dark King of the Abyss

Axe of Despair x3
Sword of Deep-Seated x3
Horn of the Unicorn x3
Black Pendant x3
United We Stand
Mage Power
Mystical Space Typhoon x2
Gravekeeper's Servant x2
Tribute to the Doomed x2
Premature Burial
Raigeki

Mirror Force


Shadi
--------------------------

Needle Worm x3
Morphing Jar #2
Goblin Attack Force x3
Aqua Madoor x2
Orion the Battle King
Millennium Golem x3
Millennium Shield x2
Cyber Jar
Ray & Temperature
Kanikabuto
Turtle Raccoon
Hitodenchak
Toad Master
The Melting Red Shadow

Chain Energy x2
Gravekeeper's Servant
Monster Reborn
Black Pendant x3
Card Destruction

Magic Thorn x2
Trap Hole x2
Magic Jammer x2
Attack and Receive x2
Enchanted Javelin x2
Negate Attack x2
Fairy Box


Yami Yugi
--------------------------

Dark Magician x3
Dark Magician Girl x2
Magician of Black Chaos x2
Summoned Skull x3
Giant Soldier of Stone x3
Mystical Elf x3
Morphing Jar #2
Cyber Jar
Horn Imp
Feral Imp
Koumori Dragon
Great White
Alpha the Magnet Warrior
Beta the Magnet Warrior
Gamma the Magnet Warrior

Dark Magic Ritual x2
Monster Reborn
Raigeki
Dark Hole
Change of Heart
Snatch Steal
Harpie's Feather Duster
Mage Power
United We Stand
Axe of Despair x2
Premature Burial
Swords of Revealing Light
Pot of Greed

Royal Decree
Mirror Force
Magic Cylinder
Ring of Destruction
Trap Hole
Magic Jammer
Negate Attack
Call of the Haunted


Weevil
--------------------------

Jirai Gumo x2
Man Eater Bug x3
Needle Worm x3
Hercules Beetle x2
Giant Flea x2
Killer Needle x2
Petit Moth
Spiked Snail x2
Hunter Spider
Big Insect x2
Basic Insect x2
Kuwagata Alpha x2
Kattapillar
Korogashi
Nightmare Scorpion
Giant Scorpion of the Tundra
Kamakiriman
Flying Kamakiri #2

Raigeki
Dark Hole
Change of Heart
Swords of Revealing Light
Megamorph x2
Pot of Greed

Trap Hole x2
Call of the Haunted
Widespread Ruin x2
Negate Attack x2
Torrential Tribute x2


Rex Raptor
--------------------------

Two Headed King Rex x3
Crawling Dragon #2 x3
Mad Sword Beast x2
Trakadon x2
Megazowler
Sword Arm of Dragon x2
Meteor Dragon
Uraby x2
Little D
Petit Dragon
Fairy Dragon
Sky Dragon x2
Wicked Dragon with the Ersatz Head
Mechaleon
One Eyed Shield Dragon
Ancient Lizard Warrior x2
Grappler
Drooling Lizard
Lesser Dragon x2
Krokodilus x2
Two Mouth Darkruler
Yamadron
Yormungarde
Anthrosaurus

Raigeki
Dark Hole
Change of Heart
Snatch Steal
Polymerization x2

Bracchio-raidus x2


Mako
--------------------------

7 Colored Fish x2
Giant Red Seasnake x2
Flying Fish x2
Crazy Fish x2
Amphibian Beast x2
The Legendary Fisherman x2
Kairyu-shin
30,000 Year White Turtle
Akihiron
Night Lizard
Guardian of the Sea
Bottom Dweller
Giant Turtle Who Feeds on Flames
Rainbow Marine Mermaid x2
Tongyo
Armored Starfish
High Tide Gyojin
Flying Penguin
Misairuzame x2
Jellyfish
Fiend Kraken
Spike Seadra
Violent Rain
Takriminos
Root Water
Sea King Dragon
Turtle Tiger
Fire Kraken
Hyosube

Umi x2
A Legendary Ocean
Raigeki

Torrential Tribute x3
Tornado Wall x2


Bonz
--------------------------

Dragon Zombie x2
Armored Zombie x2
Clown Zombie x2
Blue Eyed Silver Zombie
Mech Mole Zombie x2
Metal Guardian
Air Eater
Graveyard and the Hand of Invitation x3
Shadow Specter
The Snake Hair
Phantom Ghost
Magical Ghost
Ghoul with an Appetite
Morinphen
Dark Chimera
Neck Hunter
Ushi Oni
Bone Mouse
Corroding Shark
Dokuroizo the Grim Reaper
Temple of Skulls
Fire Reaper
Dark Assailant

Axe of Despair x2
Black Pendant x2
Sword of Deep Seated x2
Tribute to the Doomed x2
Premature Burial
Gravekeeper's Servant x2
Mystical Space Typhoon x2

Gravity Bind x2
Trap Hole x2
Call of the Dark
Call of the Grave
Ring of Destruction


Bandit Keith
--------------------------

Mechanicalchaser x2
Guardian of the Throne Room x2
Slot Machine x2
Barrel Dragon x2
Cyber-Tech Alligator x2
Pendulum Machine x2
Launcher Spider x2
Saber Slasher x2
Giant Mech Soldier
Cannon Soldier x2
Robotic Knight x2
Giga Tech Wolf
Golgoil
Giganto
Shovel Crusher
Dice Armadillo
Dharma Cannon
Cyber Commander
Holograh
Mechanical Snail

Limiter Removal x2
Change of Heart
Monster Reborn
7 Completed x3

Gamble x3
Trap Hole x3


Pegasus
--------------------------

Vorse Raider x2
Aqua Madoor x2
Relinquished x2
Thousand Eyes Idol
Rogue Doll
Red Archery Girl
Sinister Serpent
Parrot Dragon
Ryu Ran
Thousand Eyes Idol
Morphing Jar
Cyber Jar
Blue Eyes Toon Dragon
Toon Summoned Skull x2
Toon Mermaid x2

Dark Hole
Monster Reborn
Raigeki
Change of Heart
Snatch Steal
Premature Burial
Megamorph
Black Illusion Ritual x2
Toon World x2
Polymerization x2

Numinous Healer x2
Solemn Wishes x2
Life Absorbing Machine x2
Ring of Destruction
Magic Cylinder
Mirror Wall

Thousand Eyes Restrict


Mai
--------------------------

Harpie Lady x3
Blue Winged Crown x2
Faith Bird x2
Skull Redbird x2
Harpie's Pet Dragon x2
Harpie Lady Sisters x3
Peacock
Garvas
Togex
Kurama
Tyhone
Firewing Pegasus
Droll Bird
Crow Goblin

Elegant Egotist x3
Harpie's Feather Duster
Rising Air Current x2
Raigeki
Dark Hole
Black Pendant x2
Swords of Revealing Light

Aqua Chorus x2
Shadow of Eyes x2
Enchanted Javelin x2
Negate Attack x2
Ring of Destruction
Mirror Force


Kaiba
--------------------------

Blue Eyes White Dragon x3
Barrel Dragon
Cyber-Tech Alligator x3
Judge Man x2
Steel Ogre Grotto #2 x3
Vorse Raider x3
The Forgiving Maiden x3
Magician of Faith x3
La Jinn the Mystical Genie of the Lamp
Ryu-Kishin
Swordstalker
Hitosu-me Giant
Saggi the Dark Clown

Monster Reborn
Raigeki
Dark Hole
Polymerization x2
Heavy Storm
Harpie's Feather Duster
Megamorph
Premature Burial

Mirror Force
Ring of Destruction
Magic Cylinder
Magic Jammer
Attack and Receive
Just Desserts x2
Call of the Haunted
Torrential Tribute
Negate Attack

Blue Eyes Ultimate Dragon x3


Rare Hunter
--------------------------

Exodia the Forbidden One
Right Leg of the Forbidden One x3
Left Leg of the Forbidden One x3
Right Arm of the Forbidden One x3
Left Arm of the Forbidden One x3
Three Headed Geedo x2
Witch of the Black Forest x2
Sinister Serpent

Pot of Greed x3
Graceful Charity x3
Monster Reborn
Dark Hole
Swords of Revealing Light

Jar of Greed x3
Enchanted Javelin x2
Negate Attack x2
Torrential Tribute x2
Trap Hole x2
Life Absorbing Machine x2
Just Desserts x2


Arkana
--------------------------

Dark Magician (red) x3
The Illusory Gentleman x3
Aqua Madoor x3
Cannon Soldier x2
Illusionist Faceless Mage x2
Leo Wizard x2
Rock Spirit x2

Black Pendant x2
Raigeki
Premature Burial

Mirror Force
Ring of Destruction
Negate Attack x3
Trap Hole x3
Widespread Ruin x3
Enchanted Javelin x2
Fairy Box x2
Torrential Tribute x2
Gamble x2


Strings
--------------------------

Humanoid Slime x3
Worm Drake x3
Rogue Doll x3
Destroyer Golem x2
Millennium Golem x2
Steel Ogre Grotto #2 x2
Illusionist Faceless Mage x2

Raigeki
Polymerization x2
Gravekeeper's Servant x2
Black Pendant x2
Axe of Despair x2
Mystical Space Typhoon x2
Premature Burial

Trap Hole x2
Magic Jammer x2
Jar of Greed x2
Solemn Wishes x2
Mirror Force
Magic Cylinder
Ring of Destruction

Humanoid Worm Drake x2


Espa Roba
--------------------------

Maha Vailo x3
The Illusory Gentleman
Neo the Magic Swordsman
The Judgement Hand x3
Giant Soldier of Stone x3
Ancient Sorcerer
Sorcerer of the Doomed
Ill Witch
Rock Spirit
LaMoon x2
Spirit of the Winds x2
Spirit of the Mountain x2
Jinzo
Leo Wizard x2

Axe of Despair x2
Sword of Deep Seated x2
Horn of the Unicorn
Black Pendant x2
Tribute to the Doomed x2
Monster Reborn
Change of Heart
Mystical Space Typhoon x2
Harpie's Feather Duster
Snatch Steal
Swords of Revealing Light
Dark Hole
Raigeki


Lumis and Umbra
--------------------------

Shining Abyss x3
Grand Tiki Elder x3
Melchid the Four-Face Beast x3
Masked Clown x3
Masked Sorcerer x3
Mask of Darkness x3
Magician of Faith
The Masked Beast x2

Curse of the Masked Beast x2
Mask of Brutality
Black Pendant x2
Mystical Space Typhoon x2
Change of Heart

Mask of Weakness x2
Backup Soldier x2
Widespread Ruin x2
Jar of Greed x2
Negate Attack x2
Mirror Force
Magic Cylinder


Marik
--------------------------

Vorse Raider x3
The Bistro Butcher x2
Morphing Jar x2
Morphing Jar #2 x2
Cyber Jar
Needle Worm x2
Magician of Faith x2
Man Eater Bug x2
Summoned Skull x2

Card Destruction
Black Pendant x2
Axe of Despair x2
Monster Reborn
Change of Heart
Delinquent Duo
Tribute to the Doomed x2
Mystical Space Typhoon x2

Magic Thorn x2
Magic Jammer x2
Just Desserts x2
Mirror Force
Ring of Destruction
Solemn Wishes x2


Ishizu
--------------------------

Dark Elf x2
Dunames Dark Witch x3
The Forgiving Maiden x2
Fire Princess x2
Marie the Fallen One x2
Spirit of the Harp x2
Ray & Temperature
Petit Angel
Ocubeam x2
Orion the Battle King
Winged Egg of New Life

Bright Castle x2
Black Pendant x3
Luminous Spark
Polymerization x2
Harpie's Feather Duster
Raigeki
Swords of Revealing Light
Chain Energy

Mirror Force
Magic Cylinder
Enchanted Javelin x2
Gift of the Mystical Elf x2
Solemn Wishes x2
Numinous Healer x2
Enchanted Javelin x2
Life Absorbing Machine x2
Anti Raigeki
White Hole

St. Joan x2


Odion
--------------------------

Slate Warrior x3
Man Eater Bug x3
Mask of Darkness x3
Magician of Faith x3
Morphing Jar
Judge Man x2
Millennium Shield x2
Cyber Jar

Gravekeeper's Servant x2
Chain Energy

Torrential Tribute x2
Trap Hole
Widespread Ruin x2
Light of Intervention
White Hole
Anti Raigeki
Enchanted Javelin x2
Ceasefire
Solemn Judgement
Life Absorbing Machine x2
Shadow of Eyes
Jar of Greed
Fairy Box
Negate Attack x2
Just Desserts x2
Mirror Wall


Yami Marik
--------------------------

Vorse Raider x2
Muka Muka x2
Man Eater Bug x2
Mask of Darkness x2
Magician of Faith x2
Morphing Jar #2 x2
Cyber Jar
Summoned Skull x2

Monster Reborn
Raigeki
Dark Hole
Pot of Greed
Harpie's Feather Duster
Delinquent Duo
Snatch Steal
Change of Heart
Mystical Space Typhoon x2
Axe of Despair x2
Black Pendant x2
Infinite Cards x2
Gravekeeper's Servant x2

Jar of Greed x3
Gravity Bind x2
Call of the Haunted
Mirror Force
Ring of Destruction


Yami Bakura
--------------------------
Gemini Elf x2
La Jinn the Mystical Genie of the Lamp x2
The Portrait's Secret x3
Aqua Madoor x2
Summoned Skull x2

Monster Reborn
Premature Burial
Raigeki
Dark Hole
Pot of Greed
United We Stand
Mage Power
Tribute to the Doomed x2
Mystical Space Typhoon x2
Gravekeeper's Servant x2
Spirit Message "I"
Spirit Message "N"
Spirit Message "A"
Spirit Message "L"

Ring of Destruction
Mirror Force
Magic Cylinder
Life Absorbing Machine
Destiny Board
Aqua Chorus
Solemn Wishes x2
Widespread Ruin x2
Negate Attack x2
*/	
	
	
}

unsigned int hash_string(const char* str)
{
	unsigned int hash = 0;
	while (*str) {
		hash = hash * 31 + (unsigned char)(*str);
		str++;
	}
	return hash;
}

void randomizer_main(FILE* fp)
{
    char choose_dm_t;
    fflush(stdin);
    do
    {
        if(choose_dm_t == 'Y' || choose_dm_t == 'N')
            break;
        printf("Do you want a dedicated Duel Machine Tier? Y/N \n");
        fflush(stdin);
        scanf(" %c", &choose_dm_t); // Add a space before %c to skip any leading whitespace
    } while(choose_dm_t != 'Y' && choose_dm_t != 'N');  // Corrected condition here
    
    if(choose_dm_t == 'Y')
    {       
        randomize_tier_people_duel_machine_tier(fp);
    }
    else if(choose_dm_t == 'N')
    {
        randomize_tier_people_no_duel_machine_tier(fp);
    }
    
    char choose_opp_lp;
    fflush(stdin);
    do {
        if(choose_opp_lp == 'Y' || choose_opp_lp == 'N')
            break;
        printf("Do you want the tier opponents to have random LP values? Y/N \n");
        fflush(stdin);
        scanf(" %c", &choose_opp_lp); // Added space before %c to handle any stray input
    } while(choose_opp_lp != 'Y' && choose_opp_lp != 'N');  // Corrected condition here
    
    if(choose_opp_lp == 'Y')
        randomize_tier_LP(fp);
    
    char choose_your_lp;
    fflush(stdin);
    do {
        if(choose_your_lp == 'Y' || choose_your_lp == 'N')
            break;
        printf("Do you want to have random LP values in the tiers? Y/N \n");
        fflush(stdin);
        scanf(" %c", &choose_your_lp); // Added space before %c to handle any stray input
    } while(choose_your_lp != 'Y' && choose_your_lp != 'N');  // Corrected condition here
    
    if(choose_your_lp == 'Y')
        randomize_your_tier_LP(fp);
}


int main()
{
	
	fflush(stdin);
	char choose;
	
	printf("WARNING: This will overwrite the iso file \n");
	do 
	{
		if(choose == 'N' || choose == 'Y' || choose == 'y' || choose == 'n')
			break;
		printf("continue Y/N ? \n");
		scanf("%c",&choose);
	} while (choose != 'Y' || choose != 'N' || choose != 'y' || choose != 'n');
	if(choose == 'N' || choose == 'n')
	{
		printf("bye \n");
		exit(0);
	}
	fflush(stdin);
	//int randVal = 0;
	unsigned int xseed = 0;
	FILE* fp;
	FILE* fptr;
	char seed_string[128];
	printf("Type a seed (number or string): \n"); 
	scanf("%127s",seed_string);
	if(strspn(seed_string, "0123456789") == strlen(seed_string)) {
		//If the input is purely numeric use it directly
		xseed = atoi(seed_string);
		printf("Numeric seed will be: %u\n", xseed);
	} else {
		xseed = hash_string(seed_string);
		printf("String seed hashed to: %u\n", xseed);
	}
	srand(xseed);
	fflush(stdin);
	printf("Type the filepath to the NTSC-U iso version of 'Yu-Gi-Oh! The Dawn of Destiny' (for xbox) \n(Spaces are NOT allowed; including the filename)\n *If your filename has spaces in it you will need to rename the file to not have spaces before using it here* \n(This is case sensitive) \n");
	char choose2[128];
	scanf("%127s",&choose2);
	fp = fopen(choose2, "rb+");
	//check if file opened successfully 
	if(fp == NULL)
	{
		printf("The file is not opened. The program will now exit. \n");
		exit(1); //failed to open file
	}
	else
	{
		printf("The file opened successfully. \n");
	}
	
	randomizer_main(fp);
	
	fclose(fp);
	return 0;
}