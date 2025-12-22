#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <cctype>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1024,600 }), "Chess");
	window.setPosition({ 13,13 });

	sf::Image icon;
	if (!icon.loadFromFile("E:/fluffy-octo-computing-machine/chess.png"))
		window.close(); 
	window.setIcon(icon);

	sf::Font font("E:/fluffy-octo-computing-machine/comic.ttf");
	
	sf::Angle reverse = sf::degrees(180);

	sf::Texture boardload("E:/fluffy-octo-computing-machine/chessboard.jpg");
	sf::Sprite board(boardload);
	board.setPosition({ 256,56 });
	float offSetX = 256;
	float offSetY = 56;


	const sf::Texture pieces("E:/fluffy-octo-computing-machine/ChessPiecesArray.png");
	sf::Sprite whitePawn(pieces, { {300,60},{60,60} });
	sf::Sprite blackPawn(pieces, { {300,0},{60,60} });
	blackPawn.setRotation(reverse);
	blackPawn.setOrigin({ 60,60 });
	sf::Sprite whiteRook(pieces, { {120,60},{60,60} });
	sf::Sprite blackRook(pieces, { {120,0},{60,60} });
	blackRook.setRotation(reverse);
	blackRook.setOrigin({ 60,60 });
	sf::Sprite whiteKnight(pieces, { {180,60},{60,60} });
	sf::Sprite blackKnight(pieces, { {180,0},{60,60} });
	blackKnight.setRotation(reverse);
	blackKnight.setOrigin({ 60,60 });
	sf::Sprite whiteBishop(pieces, { {240,60},{60,60} });
	sf::Sprite blackBishop(pieces, { {240,0},{60,60} });
	blackBishop.setRotation(reverse);
	blackBishop.setOrigin({ 60,60 });
	sf::Sprite whiteKing(pieces, { {60,60},{60,60} });
	sf::Sprite blackKing(pieces, { {60,0},{60,60} });
	blackKing.setRotation(reverse);
	blackKing.setOrigin({ 60,60 });
	sf::Sprite whiteQueen(pieces, { {0,60},{60,60} });
	sf::Sprite blackQueen(pieces, { {0,0},{60,60} });
	blackQueen.setRotation(reverse);
	blackQueen.setOrigin({ 60,60 });
	
	std::unordered_map<char, sf::Sprite *> pieceStorage;
	pieceStorage['p'] = &blackPawn;
	pieceStorage['P'] = &whitePawn;
	pieceStorage['r'] = &blackRook;
	pieceStorage['R'] = &whiteRook;
	pieceStorage['n'] = &blackKnight;
	pieceStorage['N'] = &whiteKnight;
	pieceStorage['b'] = &blackBishop;
	pieceStorage['B'] = &whiteBishop;
	pieceStorage['k'] = &blackKing;
	pieceStorage['K'] = &whiteKing;
	pieceStorage['q'] = &blackQueen;
	pieceStorage['Q'] = &whiteQueen;



	// Change this to change the position of pieces on board.
	std::string start = "r1bk3r/p2pBpNp/n4n2/1p1NP2P/6P1/3P4/P1P1K3/q5b1";
	
	
	
	
	
	while (window.isOpen())
	{
		while (std::optional event = window.pollEvent())
		{
			if (event->is <sf::Event::Closed>())
			{
				window.close();
			}

		}

		window.clear({ 230, 230, 230 });

		window.draw(board);
		int Xoff = 0, Yoff = 0;
		for (char x : start)
		{
			if (std::isalpha(x))
			{ 
				sf::Vector2f set = { Xoff + offSetX , Yoff + offSetY};
				pieceStorage[x]->setPosition(set);
				Xoff += 60;
				window.draw(*pieceStorage[x]);
			}
			else if ((x >= '1') && (x <= '8'))
			{
				Xoff += ((x - '0') * 60);
			}
			else if (x == '/')
			{
				Yoff += 60;
				Xoff = 0;
			}

		}

		window.display();
	}

	return 0;
}




