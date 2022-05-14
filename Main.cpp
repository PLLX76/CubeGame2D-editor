#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Windows.h>

#include <fstream>

#include "portal.h"
#include "Levels.h"
#include "TextBox.h".

#include <string>
#include <iostream>
#include <cstdlib> 
#include <vector>
#include <ctime>

#pragma region Variable
sf::RenderWindow app;

sf::Image icon;

sf::Texture player_1;
sf::Texture player_2;
sf::Sprite sprite_player;

sf::Font font;
std::string font_path = "police.ttf";

int speed = 3;

int taille = 64;

int record = 1;

int offsetX = taille, offsetY = taille;

int px = 0, py = 0;

sf::Vector2f preview;

sf::View view;

int screenW = 800, screenH = 600;
std::string title = "GameCube2D";
int resolution = 32;

sf::RectangleShape coeur;

bool fullscreen;

int latence_int = 0;

int pen = 0;

int stage = 1;

int sx = -1, sy = -1;
bool selected = false;
int portal_number = 0;

bool portal = false;
#pragma endregion

#pragma region textures

sf::Texture block_texture,
			block_casse_texture,
			portal_texture,
			champigon_texture,
			mechant_texture,
			piege_texture,
			echelle_texture,
			depart_texture,
			fin_texture,
			TNT_texture,
			air_texture,
			restart_texture;
		
sf::Texture coeur_texture;

sf::Texture save_texture,
			souris_texture;

sf::Texture fleche_droite,
			fleche_gauche,
			fleche_droite_no,
			fleche_gauche_no;

sf::Texture item_heal_texture;
sf::Texture item_up_texture;
sf::Texture item_speed_texture;
sf::Texture item_sword_texture;
#pragma endregion variable textures des blocks

#pragma region Fonction

void gestion_clavier();
void reset_vetbox(bool position_reset);
//void reset_in_vetbox(int x, int y);
void config();
void charge();
void gestion_mannette(sf::Event event);
void view_anim(sf::Event event);
void collision_mouse();
void latence(bool latence, int latence_max);

#pragma endregion fonction declaration

#pragma region Rect
sf::RectangleShape  block_rect,
					block_casse_rect,
					portal_rect,
					champigon_rect,
					mechant_rect,
					piege_rect,
					echelle_rect,
					depart_rect,
					fin_rect,
					heal_rect,
					TNT_rect,
					air_rect,
					save_rect,
					souris_rect,
					select_rect,
					select_portal_rect,
					restart_rect,
					item_sword_rect,
					item_speed_rect,
					item_up_rect,
					item_heal_rect;
#pragma endregion

//site color https://htmlcolorcodes.com/fr/

int main()
{
	config();
	charge();

	if (fullscreen) {
		screenW = sf::VideoMode::getFullscreenModes()[0].width;
		screenH = sf::VideoMode::getFullscreenModes()[0].height;
		app.create(sf::VideoMode(screenW, screenH, resolution), title, sf::Style::Fullscreen);
	}
	if (!fullscreen) app.create(sf::VideoMode(screenW, screenH, resolution), title, sf::Style::Default);
	app.setFramerateLimit(60);
	if (!icon.loadFromFile(("resourcespack/" + resourcespack + "/mechant.png").c_str())) if (!icon.loadFromFile("resourcespack/default/mechant.png")) std::cout << "error icon ligne 127" << std::endl;
	app.setIcon(500, 500, icon.getPixelsPtr());

#pragma region chargement image
	if (!block_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/block.png").c_str())) if (!block_texture.loadFromFile("resourcespack/default/texture/block.png")) std::cout << "erreur d'image chargement 'block.png'" << std::endl;
	if (!block_casse_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/block_casse.jpg").c_str())) if (!block_casse_texture.loadFromFile("resourcespack/default/texture/block_casse.jpg")) std::cout << "erreur d'image chargement 'block_casse.jpg'" << std::endl;
	if (!TNT_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/TNT.jpg").c_str())) if (!TNT_texture.loadFromFile("resourcespack/default/texture/TNT.jpg")) std::cout << "erreur d'image chargement 'TNT.jpg'" << std::endl;
	if (!champigon_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/champignon.png").c_str())) if (!champigon_texture.loadFromFile("resourcespack/default/texture/champignon.png")) std::cout << "erreur d'image chargement 'champignon.png'" << std::endl;
	if (!mechant_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/mechant.png").c_str())) if (!mechant_texture.loadFromFile("resourcespack/default/texture/mechant.png")) std::cout << "erreur d'image chargement 'mechant.png'" << std::endl;
	if (!piege_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/piege.png").c_str())) if (!piege_texture.loadFromFile("resourcespack/default/texture/piege.png")) std::cout << "erreur d'image chargement 'piege.png'" << std::endl;
	if (!echelle_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/ladders.png").c_str())) if (!echelle_texture.loadFromFile("resourcespack/default/texture/ladders.png")) std::cout << "erreur d'image chargement 'ladders.png'" << std::endl;
	if (!depart_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/champi.png").c_str())) if (!depart_texture.loadFromFile("resourcespack/default/texture/champi.png")) std::cout << "erreur d'image chargement 'champi.png'" << std::endl;
	if (!portal_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/portal.png").c_str())) if (!portal_texture.loadFromFile("resourcespack/default/texture/portal.png")) std::cout << "erreur d'image chargement 'portal.png'" << std::endl;
	if (!fin_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/fin.png").c_str())) if (!fin_texture.loadFromFile("resourcespack/default/texture/fin.png")) std::cout << "erreur chargement d'image 'fin.png'" << std::endl;
	if (!fleche_droite.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-droite.png").c_str())) if (!fleche_droite.loadFromFile("resourcespack/default/texture/fleche-droite.png")) std::cout << "erreur de chargement d'image 'fleche-droite.png'" << std::endl;
	if (!fleche_gauche.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-gauche.png").c_str())) if (!fleche_gauche.loadFromFile("resourcespack/default/texture/fleche-gauche.png")) std::cout << "erreur de chargement d'image 'fleche-gauche.png'" << std::endl;
	if (!fleche_droite_no.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-droite-no.png").c_str())) if (!fleche_droite.loadFromFile("resourcespack/default/texture/fleche-droite-no.png")) std::cout << "erreur de chargement d'image 'fleche-droite-no.png'" << std::endl;
	if (!fleche_gauche_no.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-gauche-no.png").c_str())) if (!fleche_gauche.loadFromFile("resourcespack/default/texture/fleche-gauche-no.png")) std::cout << "erreur de chargement d'image 'fleche-gauche-no.png'" << std::endl;
	if (!coeur_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/coueur_plein.png").c_str())) if (!coeur_texture.loadFromFile("resourcespack/default/texture/coueur_plein.png")) std::cout << "erreur d'image chargement 'coueur_plein.png'" << std::endl;
	if (!air_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/air.png").c_str())) if (!air_texture.loadFromFile("resourcespack/default/texture/air.png")) std::cout << "erreur d'image chargement 'air.png'" << std::endl;
	if (!save_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/save.png").c_str())) if (!save_texture.loadFromFile("resourcespack/default/texture/save.png")) std::cout << "erreur d'image chargement 'save.png'" << std::endl;
	if (!souris_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/souris.png").c_str())) if (!souris_texture.loadFromFile("resourcespack/default/texture/souris.png")) std::cout << "erreur d'image chargement 'souris.png'" << std::endl;
	if (!restart_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/restart.png").c_str())) if (!restart_texture.loadFromFile("resourcespack/default/texture/restart.png")) std::cout << "erreur d'image chargement 'restart.png'" << std::endl;
	if (!item_heal_texture.loadFromFile(("resourcespack/" + resourcespack + "/item/item_potion.png").c_str())) if (!item_heal_texture.loadFromFile("resourcespack/default/item/item_potion.png")) std::cout << "erreur d'image chargement 'item_potion.png'" << std::endl;
	if (!item_sword_texture.loadFromFile(("resourcespack/" + resourcespack + "/item/sword.png").c_str())) if (!item_sword_texture.loadFromFile("resourcespack/default/item/sword.png")) std::cout << "erreur d'image chargement 'sword_inverse.png'" << std::endl;
	if (!item_up_texture.loadFromFile(("resourcespack/" + resourcespack + "/item/Up.png").c_str())) if (!item_up_texture.loadFromFile("resourcespack/default/item/Up.png")) std::cout << "erreur d'image chargement 'Up.png'" << std::endl;
	if (!item_speed_texture.loadFromFile(("resourcespack/" + resourcespack + "/item/speed.png").c_str())) if (!item_speed_texture.loadFromFile("resourcespack/default/item/speed.png")) std::cout << "erreur d'image chargement 'speed.png'" << std::endl;
#pragma endregion chargement des texture des block

	reset_vetbox(true);

#pragma region elements

	if (!player_1.loadFromFile(("resourcespack/" + resourcespack + "/texture/fantome-1.png").c_str())) if (!player_1.loadFromFile("resourcespack/default/texture/fantome-1.png")) std::cout << "erreur chargement d'image 'fantome-1.png'" << std::endl;
	if (!player_2.loadFromFile(("resourcespack/" + resourcespack + "/texture/fantome-2.png").c_str())) if (!player_2.loadFromFile("resourcespack/default/texture/fantome-2.png")) std::cout << "erreur chargement d'image 'fantome-2.png'" << std::endl;

	player_1.setSmooth(true);
	player_2.setSmooth(true);
	sprite_player.setTexture(player_1);

	if (!font.loadFromFile(("resourcespack/" + resourcespack + "/police/" + font_path).c_str())) if (!font.loadFromFile("resourcespack/default/police/police.ttf")) std::cout << "erreur de chargement de police de charact�re 'police.ttf'" << std::endl;


	Textbox text1(20, sf::Color::Black, true);
	text1.setPosition(sf::Vector2f{ 50, 50 });
	text1.setLimit(true, 30);
	text1.setFont(font);

	Textbox text2(20, sf::Color::Black, true);
	text2.setPosition(sf::Vector2f{ 50, 50 });
	text2.setLimit(true, 30);
	text2.setFont(font);

	Textbox text3(20, sf::Color::Black, true);
	text3.setPosition(sf::Vector2f{ 50, 50 });
	text3.setLimit(true, 30);
	text3.setFont(font);

#pragma endregion

#pragma region Rect_init
	
	sf::Vector2f position(screenW / 2, screenH / 2);
	position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);
	
	block_rect.setTexture(&block_texture);
	block_rect.setSize(sf::Vector2f(30,30));
	block_rect.setPosition(position.x + 10, position.y);

	block_casse_rect.setTexture(&block_casse_texture);
	block_casse_rect.setSize(sf::Vector2f(30, 30));
	block_casse_rect.setPosition(position.x + 10, position.y + 40 *1);

	portal_rect.setTexture(&portal_texture);
	portal_rect.setSize(sf::Vector2f(30, 30));
	portal_rect.setPosition(position.x + 10, position.y + (40) * 2);

	champigon_rect.setTexture(&champigon_texture);
	champigon_rect.setSize(sf::Vector2f(30, 30));
	champigon_rect.setPosition(position.x + 10, position.y + (40) * 3);

	mechant_rect.setTexture(&mechant_texture);
	mechant_rect.setSize(sf::Vector2f(30, 30));
	mechant_rect.setPosition(position.x + 10, position.y + (40) * 4);

	piege_rect.setTexture(&piege_texture);
	piege_rect.setSize(sf::Vector2f(30, 30));
	piege_rect.setPosition(position.x + 10, position.y + (40) * 5);

	echelle_rect.setTexture(&echelle_texture);
	echelle_rect.setSize(sf::Vector2f(30, 30));
	echelle_rect.setPosition(position.x + 10, position.y + (40) * 6);

	depart_rect.setTexture(&depart_texture);
	depart_rect.setSize(sf::Vector2f(30, 30));
	depart_rect.setPosition(position.x + 10, position.y + (40) * 7);

	fin_rect.setTexture(&fin_texture);
	fin_rect.setSize(sf::Vector2f(30, 30));
	fin_rect.setPosition(position.x + 10, position.y +  (40) * 8);

	heal_rect.setTexture(&coeur_texture);
	heal_rect.setSize(sf::Vector2f(30, 30));
	heal_rect.setPosition(position.x + 10, position.y + (40) * 9);

	TNT_rect.setTexture(&TNT_texture);
	TNT_rect.setSize(sf::Vector2f(30, 30));
	TNT_rect.setPosition(position.x + 10, position.y + (40) * 10);

	air_rect.setTexture(&air_texture);
	air_rect.setSize(sf::Vector2f(30, 30));
	air_rect.setPosition(position.x + 10, position.y + (40) * 11);

	souris_rect.setTexture(&souris_texture);
	souris_rect.setSize(sf::Vector2f(30, 30));
	souris_rect.setPosition(position.x + 10, position.y + (40) * 12);
	
	select_rect.setSize(sf::Vector2f(taille, taille));
	select_rect.setOutlineColor(sf::Color::Red);
	select_rect.setOutlineThickness(-5.0f);
	select_rect.setFillColor(sf::Color::Transparent);

	select_portal_rect.setSize(sf::Vector2f(taille, taille));
	select_portal_rect.setOutlineColor(sf::Color::Blue);
	select_portal_rect.setOutlineThickness(-5.0f);
	select_portal_rect.setFillColor(sf::Color::Transparent);

	position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 + (screenH / 2);

	item_heal_rect.setTexture(&item_heal_texture);
	item_heal_rect.setSize(sf::Vector2f(50, 50));
	item_heal_rect.setPosition(position.x + (60) * 1, position.y - 60);

	item_speed_rect.setTexture(&item_speed_texture);
	item_speed_rect.setSize(sf::Vector2f(50, 50));
	item_speed_rect.setPosition(position.x + (60) * 2, position.y - 60);

	item_sword_rect.setTexture(&item_sword_texture);
	item_sword_rect.setSize(sf::Vector2f(50, 50));
	item_sword_rect.setPosition(position.x + (60) * 3, position.y - 60);

	item_up_rect.setTexture(&item_up_texture);
	item_up_rect.setSize(sf::Vector2f(50, 50));
	item_up_rect.setPosition(position.x + (60) * 4, position.y - 60);

	position.x = sprite_player.getPosition().x + taille / 2 + (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);

	save_rect.setTexture(&save_texture);
	save_rect.setSize(sf::Vector2f(50, 50));
	save_rect.setPosition(position.x - 60, position.y);

#pragma endregion


	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				std::cout << "fermeture la fenetre" << std::endl;
				app.close();
				break;

			case sf::Event::TextEntered:
				switch (stage)
				{
				case 1 :
					text1.typedOn(event);
				case 2 :
					text2.typedOn(event);
				case 3 :
					text3.typedOn(event);
				default:
					break;
				}
				
			}
		}

		screenH = app.getSize().y;
		screenW = app.getSize().x;

		sf::Vector2f position(screenW / 2, screenH / 2);
		position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
		position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);

		latence(false, 0);
		view_anim(event);

		if (stage == 1)
		{	
			text1.setSelected(true);
			text1.setPosition({ position.x + 50, position.y + 50 });
			portal_number = 0;

			app.clear();

			sf::Text text;
			text.setFont(font);
			text.setPosition(position);
			text.setString("quel niveau voulez vous creer / modifier");

			app.draw(text);

			text1.drawTo(app);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (latence_int == 0  && text1.getText() != "")
				{
					std::ifstream ifs(("resourcespack/" + resourcespack + "/Levels/level" + text1.getText() + ".txt").c_str());

					text1.setSelected(false);
					level = stoi(text1.getText());

					if (ifs.is_open()) { stage = 4;  ChargeLevels(level); ChargePortal(level); reset_vetbox(true); }
					else stage = 2;

					ifs.close();
					latence(true, 30);
				}					
			}			
		}
		else if (stage == 2)
		{
			text2.setSelected(true);
			text2.setPosition({ position.x + 50, position.y + 50 });
			app.clear();

			sf::Text text;
			text.setFont(font);
			text.setPosition(position);
			text.setString("hauteur");

			app.draw(text);

			text2.drawTo(app);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (latence_int == 0 && text2.getText() != "")
				{
					text2.setSelected(false);
					heightmap = stoi(text2.getText());
					stage = 3;
					latence(true, 30);
				}
			}	
		}
		else if (stage == 3)
		{
			text3.setSelected(true);
			text3.setPosition({ position.x + 50, position.y + 50 });

			app.clear();

			sf::Text text;
			text.setFont(font);
			text.setPosition(position);
			text.setString("largeur");

			app.draw(text);

			text3.drawTo(app);

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				if (latence_int == 0 &&  text3.getText() != "")
				{
					text3.setSelected(false);
					withtmap = stoi(text3.getText());
					std::ofstream ofs(("resourcespack/" + resourcespack + "/Levels/level" + std::to_string(level) + ".txt").c_str());

					tapmap.resize(heightmap);
					for (int i = 0; i < tapmap.size(); i++)
						tapmap[i].resize(withtmap);
					tapmapportal.resize(heightmap);
					for (int i = 0; i < tapmap.size(); i++)
						tapmapportal[i].resize(withtmap);

					if (ofs.is_open())
					{
						ofs << heightmap << std::endl;
						ofs << withtmap << std::endl;

						for (int y = 0; y < heightmap; y++)
						{
							for (int x = 0; x < withtmap; x++)
							{
								tapmap[y][x] = 0;
								ofs << tapmap[y][x] << " ";
							}
							ofs << std::endl;
						}
					}
					ofs.close();

					std::ofstream ofs_portal(("resourcespack/" + resourcespack + "/Levels/level" + std::to_string(level) + "portal.txt").c_str());
					if (ofs_portal.is_open())
					{

						for (int y = 0; y < heightmap; y++)
						{
							for (int x = 0; x < withtmap; x++)
							{
								tapmapportal[y][x] = 0;
								ofs_portal << tapmapportal[y][x] << " ";
							}
							ofs_portal << std::endl;
						}
					}
					ofs_portal.close();

					ChargeLevels(level);
					ChargePortal(level);
					reset_vetbox(true);

					stage = 4;
				}
			}
		}
		else if (stage == 4)
		{

#pragma region set Position

		block_rect.setPosition(position.x + 10, position.y);
		block_casse_rect.setPosition(position.x + 10, position.y + 40 * 1);
		portal_rect.setPosition(position.x + 10, position.y + (40) * 2);
		champigon_rect.setPosition(position.x + 10, position.y + (40) * 3);
		mechant_rect.setPosition(position.x + 10, position.y + (40) * 4);
		piege_rect.setPosition(position.x + 10, position.y + (40) * 5);
		echelle_rect.setPosition(position.x + 10, position.y + (40) * 6);
		depart_rect.setPosition(position.x + 10, position.y + (40) * 7);
		fin_rect.setPosition(position.x + 10, position.y + (40) * 8);
		heal_rect.setPosition(position.x + 10, position.y + (40) * 9);
		TNT_rect.setPosition(position.x + 10, position.y + (40) * 10);
		air_rect.setPosition(position.x + 10, position.y + (40) * 11);
		souris_rect.setPosition(position.x + 10, position.y + (40) * 12);

		position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
		position.y = sprite_player.getPosition().y + taille / 2 + (screenH / 2);

		item_up_rect.setPosition(position.x + (60) * 4, position.y - 60);
		item_sword_rect.setPosition(position.x + (60) * 3, position.y - 60);
		item_speed_rect.setPosition(position.x + (60) * 2, position.y - 60);
		item_heal_rect.setPosition(position.x + (60) * 1, position.y - 60);

		position.x = sprite_player.getPosition().x + taille / 2 + (screenW / 2);
		position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);

		save_rect.setPosition(position.x - 60, position.y);
		restart_rect.setPosition(position.x - 120,position.y);


#pragma endregion

			collision_mouse();

			gestion_clavier();
			gestion_mannette(event);

			app.clear();
			

			sprite_player.setPosition(px, py);

		
			for (int i = 0; i < vecbox.size(); i++) { app.draw(vecbox[i]); }

#pragma region Rect draw

			app.draw(block_rect);
			app.draw(block_casse_rect);
			app.draw(portal_rect);
			app.draw(champigon_rect);
			app.draw(mechant_rect);
			app.draw(piege_rect);
			app.draw(block_rect);
			app.draw(echelle_rect);
			app.draw(depart_rect);
			app.draw(fin_rect);
			app.draw(heal_rect);
			app.draw(TNT_rect);
			app.draw(air_rect);
			app.draw(souris_rect);
			app.draw(select_rect);
			app.draw(item_heal_rect);
			app.draw(item_speed_rect);
			app.draw(item_sword_rect);
			app.draw(item_up_rect);
			if(selected|| portal) app.draw(select_portal_rect);
			app.draw(save_rect);
			app.draw(restart_rect);

#pragma endregion paul est beau


			app.draw(sprite_player);
		}
		

		app.display();
	}

}
void view_anim(sf::Event event)
{
	view.reset(sf::FloatRect(0, 0, screenW, screenH));
	sf::Vector2f position(screenW / 2, screenH / 2);
	position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);
	view.reset(sf::FloatRect(position.x, position.y, screenW, screenH));
	app.setView(view);
}
void collision_mouse() {
	bool pen_is_pressed = false;

	int top = 0;
	int bottom = top + 50;
	int left =  screenW - 60;
	int right = left + 50;
	
	if (sf::Mouse::getPosition(app).x >= left && sf::Mouse::getPosition(app).x <= right && sf::Mouse::getPosition(app).y >= top && sf::Mouse::getPosition(app).y <= bottom)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			std::cout << "save" << std::endl;
			std::ofstream ofs(("resourcespack/" + resourcespack + "/Levels/level" + std::to_string(level) + ".txt").c_str());

			if (ofs.is_open())
			{
				ofs << heightmap << std::endl;
				ofs << withtmap << std::endl;

				for (int y = 0; y < heightmap; y++)
				{
					for (int x = 0; x < withtmap; x++)
					{
						ofs << tapmap[y][x] << " ";
					}
					ofs << std::endl;
				}
			}
			ofs.close();
			std::ofstream ofs_portal(("resourcespack/" + resourcespack + "/Levels/level" + std::to_string(level) + "portal.txt").c_str());

			if (ofs_portal.is_open())
			{
				for (int y = 0; y < heightmap; y++)
				{
					for (int x = 0; x < withtmap; x++)
					{
						ofs_portal << tapmapportal[y][x] << " ";
					}
					ofs_portal << std::endl;
				}
			}
			ofs_portal.close();
		}
	}
	else {
		sf::Vector2f position(screenW / 2, screenH / 2);

		for (int i = 0; i < 13; i++)
		{
			int top = (40 * i);
			int bottom = top + 30;
			int left =  10;
			int right = left + 30;

			if (sf::Mouse::getPosition(app).x >= left && sf::Mouse::getPosition(app).x <= right && sf::Mouse::getPosition(app).y >= top && sf::Mouse::getPosition(app).y <= bottom)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (i + 1 == 13) pen = 40;
					else {
						if (i + 1 == 12) pen = 0;
						else pen = i + 1;
					}
					std::cout << "pen = " << pen << std::endl;
					pen_is_pressed = true;
				}
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			for (int i = 0; i < 4; i++)
			{
				int top = screenH - 60;
				int bottom = top + 30;
				int left = 60 + (60) * i;
				int right = left + 30;

				std::cout << top << std::endl;

				if (sf::Mouse::getPosition(app).x >= left && sf::Mouse::getPosition(app).x <= right && sf::Mouse::getPosition(app).y >= top && sf::Mouse::getPosition(app).y <= bottom)
				{

					switch (i + 1)
					{
					case 1:
						pen = 50;
						break;
					case 2:
						pen = 53;
						break;
					case 3:
						pen = 51;
						break;
					case 4:
						pen = 52;
						break;
					default:
						break;
					}
					std::cout << "pen = " << pen << std::endl;
					pen_is_pressed = true;

				}
			}
		}
		if (!pen_is_pressed)
		{
			position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
			position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);

			for (int y = 0; y < heightmap; y++)
			{
				for (int x = 0; x < withtmap; x++)
				{
					int top = y * taille - position.y;
					int bottom = top + 64;
					int left = x * taille - position.x;
					int right = left + 64;

					if (sf::Mouse::getPosition(app).x >= left && sf::Mouse::getPosition(app).x <= right && sf::Mouse::getPosition(app).y >= top && sf::Mouse::getPosition(app).y <= bottom)
					{
						select_rect.setPosition(x*taille, y*taille);
						if (selected) select_rect.setOutlineColor(sf::Color::Blue);else select_rect.setOutlineColor(sf::Color::Red);
						if (tapmap[y][x] == 3) {
							sf::Vector2f vector2f;

							for (int y2 = 0; y2 < heightmap; y2++)
							{
								for (int x2 = 0; x2 < withtmap; x2++)
								{
									if (tapmapportal[y2][x2] == tapmapportal[y][x]) {
										if (y2 != y || x2 != x)
										{
											vector2f.x = x2 * taille;
											vector2f.y = y2 * taille;
										}
									}
								}
							}
							select_portal_rect.setPosition(vector2f);
							portal = true;
						}
						else { select_portal_rect.setPosition(sx * taille, sy * taille); portal = false; }
						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							if (pen == 40)
							{
								if (latence_int == 0)
								{
									if (selected)
									{
										if (y == sy && x == sx);
										else
										{
											sf::Vector2i vector2i;
											bool portal_exits = false;

											for (int y2 = 0; y2 < heightmap; y2++)
											{
												for (int x2 = 0; x2 < withtmap; x2++)
												{
													if (tapmapportal[y2][x2] == tapmapportal[sy][sx]) {
														if (y2 != sy || x2 != sx)
														{
															portal_exits = true;
															vector2i.x = x2;
															vector2i.y = y2;
														}
													}
												}
											}
											if (portal_exits)
											{
												tapmapportal[vector2i.y][vector2i.x] = 0;
											}
											tapmapportal[y][x] = tapmapportal[sy][sx];
											selected = false;
										}
									}
									else if (tapmap[y][x] == 3)
									{
										sy = y, sx = x;
										selected = true;
										if (tapmapportal[y][x] == 0)
										{
											portal_number++;
											tapmapportal[y][x] = portal_number;
										}
										else tapmapportal[y][x] = tapmapportal[y][x];
									}
									latence(true, 10);
								}
							}
							else {
								selected = false;
								tapmap[y][x] = pen;
								reset_vetbox(false);
							}
						}
					}
				}
			}
			left = screenW - 120;
			right = left + 50;

			if (sf::Mouse::getPosition(app).x >= left && sf::Mouse::getPosition(app).x <= right && sf::Mouse::getPosition(app).y >= top && sf::Mouse::getPosition(app).y <= bottom)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					stage = 1;
					latence(true, 30);
				}
			}
		}
	}
}
#pragma region Variable
int fois = 0;
bool echelle_monter = false;
int py_avant = 0;
bool tp = false;
int tp_int = 0;
#pragma endregion Variable pour collision et clavier
void gestion_clavier()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		sprite_player.setTexture(player_2);
		px += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		sprite_player.setTexture(player_1);
		px -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		py += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		py -= speed;
	}
}
void reset_vetbox(bool position_reset)
{
	vecbox.clear();
	//vecbox.resize(withtmap * heightmap);

	for (int y = 0; y < heightmap; y++)
	{
		for (int x = 0; x < withtmap; x++)
		{
			if (tapmap[y][x] == 1) {
				//block
				sf::RectangleShape block(sf::Vector2f(offsetX, offsetY));
				//block.setFillColor(sf::Color::Red);
				block.setTexture(&block_texture);
				block.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(block);
			}
			if (tapmap[y][x] == 2) {
				//block_casse
				sf::RectangleShape block_casse(sf::Vector2f(offsetX, offsetY));
				//block_casse.setFillColor(sf::Color(117,10,10,255));
				block_casse.setTexture(&block_casse_texture);
				block_casse.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(block_casse);
			}
			if (tapmap[y][x] == 3) {
				//portal
				sf::RectangleShape portal(sf::Vector2f(offsetX, offsetY));
				//portal.setFillColor(sf::Color::Blue);
				portal.setTexture(&portal_texture);
				portal.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(portal);
			}
			if (tapmap[y][x] == 4) {
				//champignon
				sf::RectangleShape champignon(sf::Vector2f(offsetX, offsetY));
				//champignon.setFillColor(sf::Color::Green);
				champignon.setTexture(&champigon_texture);
				champignon.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(champignon);
			}
			if (tapmap[y][x] == 5) {
				//mechant
				sf::RectangleShape mechant(sf::Vector2f(offsetX, offsetY));
				//mechant.setFillColor(sf::Color::Yellow);
				mechant.setTexture(&mechant_texture);
				mechant.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(mechant);
			}
			if (tapmap[y][x] == 6) {
				//piege
				sf::RectangleShape piege(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				piege.setTexture(&piege_texture);
				piege.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(piege);
			}
			if (tapmap[y][x] == 7) {
				//echelle
				sf::RectangleShape echelle(sf::Vector2f(offsetX, offsetY * 3));
				//echelle.setFillColor(sf::Color::White);
				echelle.setTexture(&echelle_texture);
				echelle.setPosition(sf::Vector2f(x * offsetX, y * offsetY - offsetY * 2));
				vecbox.push_back(echelle);
			}
			if (tapmap[y][x] == 8) {
				//debut
				sf::RectangleShape debut(sf::Vector2f(offsetX * 4, offsetY * 4));
				//debut.setFillColor(sf::Color(80, 220,255,255));
				debut.setTexture(&depart_texture);
				debut.setPosition(sf::Vector2f(x * offsetX - offsetX * 4 / 2 + 50, y * offsetY - offsetY * 3 + 10));
				if (position_reset)
				{
					px = debut.getPosition().x + offsetX * 4 / 2;
					py = debut.getPosition().y + offsetY * 3 + 5;
				}
				vecbox.push_back(debut);
			}
			if (tapmap[y][x] == 9) {
				//fin
				sf::RectangleShape fin(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				fin.setTexture(&fin_texture);
				fin.setPosition(sf::Vector2f(x * offsetX, y * offsetY + 10));
				vecbox.push_back(fin);
			}
			if (tapmap[y][x] == 10) {
				//block heal
				sf::RectangleShape block_heal(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				block_heal.setTexture(&coeur_texture);
				block_heal.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(block_heal);
			}
			if (tapmap[y][x] == 11) {
				//TNT
				sf::RectangleShape TNT(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				TNT.setTexture(&TNT_texture);
				TNT.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(TNT);
			}
			if (tapmap[y][x] == 50) {
				//heal
				sf::RectangleShape item_heal(sf::Vector2f(offsetX, offsetY));
				item_heal.setTexture(&item_heal_texture);
				item_heal.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(item_heal);
			}
			if (tapmap[y][x] == 51) {
				//block
				sf::RectangleShape item_sword(sf::Vector2f(offsetX, offsetY));
				item_sword.setTexture(&item_sword_texture);
				item_sword.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(item_sword);
			}
			if (tapmap[y][x] == 52) {
				//block
				sf::RectangleShape item_up(sf::Vector2f(offsetX, offsetY));
				item_up.setTexture(&item_up_texture);
				item_up.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(item_up);
			}
			if (tapmap[y][x] == 53) {
				//block
				sf::RectangleShape item_speed(sf::Vector2f(offsetX, offsetY));
				item_speed.setTexture(&item_speed_texture);
				item_speed.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(item_speed);
			}
		}
	}
}
void config()
{
	std::ifstream ifs(("resourcespack/" + resourcespack + "/Config/window.ini").c_str());

	std::string string_r;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> screenW >> screenH;
		ifs >> resolution;
		ifs >> fullscreen;
		ifs >> string_r;
		ifs >> string_r;
		ifs >> resourcespack;
		ifs >> level;
		ifs >> font_path;
	}
	ifs.close();
}
void charge() {
	ChargeLevels(level);
	ChargePortal(level);
	if (level == 0)
	{
		level++;
		ChargeLevels(level);
		ChargePortal(level);
	}

}
void gestion_mannette(sf::Event event)
{
	int JoystickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	int JoystickY = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);

	if (JoystickX > 1)
	{
		sprite_player.setTexture(player_2);
		px += speed;
	}
	if (JoystickX < -1)
	{
		sprite_player.setTexture(player_1);
		px -= speed;
	}
	if (JoystickY > 1)
	{
		py += speed;
	}
	if (JoystickY < -1)
	{
		py -= speed;
	}
}
int max_latence = 10;
void latence(bool latence, int latence_max) {
	if (latence_max != 0) max_latence = latence_max;
	if (latence) latence_int++;
	if (latence_int != 0)
	{
		latence_int++;
		if (latence_int == max_latence)
		{
			latence_int = 0;
		}
	}
}