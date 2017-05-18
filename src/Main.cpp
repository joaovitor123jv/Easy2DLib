//This file is only to test this engine
#include <iostream>
#include "Window/Window.hpp"
#include "Rectangle/Rectangle.hpp"
#include "Image/Image.hpp"
#include "Text/Text.hpp"
#include "Button/Button.hpp"
#include "TextBox/TextBox.hpp"
// #include <math.h>

using namespace std;

int main()
{
	bool close = false;
	bool testTextEnabled = false;

	Window tela("Tela de Teste", 600, 400);
	tela.setDrawColor({150,150,255,255});

	tela.setResizable(true);

	Image image = Image();
	image.load(&tela);


	Text text = Text();
	text.setWindow(&tela);
	text.setFontSize(40);
	text.setColor({255, 255, 255});
	text.setText("Texto aqui");
	text.update();

	Text testText= Text();
	testText.setWindow(&tela);
	testText.setFontSize(40);
	testText.setColor({0, 0, 0});
	testText.setPosition(200, 200);
	testText.setText("Texto de teste");
	testText.update();


	Button btSair = Button();
	btSair.setWindow(&tela);
	btSair.setText("Sair");
	btSair.setPosition(300, 300);
	btSair.setOutsideColor(52, 73, 94);
	btSair.setInsideColor(44, 62, 80);
	btSair.setClickColor(127, 140, 141);
	btSair.setTextColor(250,250,250);


	Button btTeste = Button();
	btTeste.setWindow(&tela);
	btTeste.setText(" TESTE ");
	btTeste.setPosition( 100, 300 );

	TextBox txBx = TextBox();
	txBx.setSize(300, 50);
	txBx.setPosition(200, 100);
	txBx.setColor(255, 255, 255);
	txBx.setTextColor(0,0,0);

	TextBox tbGeral = TextBox();
	tbGeral.setSize(400, 50);
	tbGeral.setPosition(100, 10);
	tbGeral.setColor(244, 244, 244);
	tbGeral.setTextColor(3, 3, 3);

	Rectangle retangulo;
	retangulo.setLogs(true);
	retangulo.setColor(0, 255, 255);
	retangulo.setPosition(0, 300);
	retangulo.setSize(100,100);

	while(!close)
	{
		while(tela.getEvent())
		{
			if(tela.getClose())
			{
				close = true;
				break;
			}
		
			txBx.listener(&tela);
			tbGeral.listener(&tela);
			if(btSair.listener())
			{
				close = true;
				break;
			}
			
			if(btTeste.listener())
			{
				if(testTextEnabled)
				{
					testTextEnabled = false;
				}
				else
				{
					testTextEnabled = true;
				}
			}

			if(tela.getKeyDown())
			{
				switch(tela.getKey())
				{
					case SDLK_w:
						retangulo.setY(retangulo.getY() - 1);
						break;
					case SDLK_s:
						retangulo.setY(retangulo.getX() + 1);
						break;
					case SDLK_a:
						retangulo.setX(retangulo.getX() - 1);
						break;
					case SDLK_d:
						retangulo.setX(retangulo.getX() + 1);
						break;
					default:
						break;
				}
			}
			else if(tela.getKeyUp())
			{

			}
		}

		image.print(&tela);
		if(testTextEnabled)
		{
			testText.print();
		}
		text.print();
		retangulo.print(&tela);
		txBx.print(&tela);
		tbGeral.print(&tela);
		btTeste.print();
		btSair.print();
		

		tela.update();
		SDL_Delay(30);
	}
	return 0;
}
