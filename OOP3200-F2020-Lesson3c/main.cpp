/*Name - Devanshu Dave
 *ID - 100785733
 */


#include <iomanip>
#include <iostream>
#include <map>

#include <vector>
#include <fstream>
#include <cstdlib>
#include "GameObject.h"
#include "Vector3D.h"

void PrintGameObjects(const std::map<std::string, GameObject*>& game_objects)
{
	std::cout << "=================================" << std::endl;
	std::cout << " Output map of Game Objects      " << std::endl;
	std::cout << "=================================" << std::endl;

	// for every game_object in gameObjects...loop
	for (const auto& game_object : game_objects)
	{
		std::cout << "Key  : " << game_object.first << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << game_object.second->ToString();
		std::cout << "---------------------------------\n" << std::endl;
	}
}

static void BuildGameObjects(std::vector<GameObject*>& game_objects, const int num = 2)
{
	for (auto count = 0; count < num; ++count)
	{
		int id;
		std::cout << "Enter the gameObject's ID: ";
		std::cin >> id;
		Vector2D<float> point;
		std::cout << "Enter the gameObject's Position (x, y): ";
		std::cin >> point;
		std::cout << "\n--------------------------------------------------------------" << std::endl;
		std::cout << "You Entered " << id << " for the gameObject's ID " << std::endl;
		std::cout << "You Entered " << point << " for the gameObject's Position" << std::endl;
		std::cout << "--------------------------------------------------------------\n" << std::endl;
		auto* gameObject = new GameObject(id, point);
		game_objects.push_back(gameObject);
	}
	
}

static void CompareGameObjects(GameObject* object1, GameObject* object2)
{
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Magnitude of first gameObject is: " << object1->GetPosition().GetMagnitude() << std::endl;
	std::cout << "Magnitude of second gameObject is: " << object2->GetPosition().GetMagnitude() << std::endl;
	std::cout << "Distance between first gameObject and second gameObject is: "
		<< Vector2D<float>::Distance(object1->GetPosition(), object2->GetPosition()) << std::endl;
	std::cout << "--------------------------------------------------------------\n" << std::endl;

	std::cout << "The angle (in degrees) from the first gameObject to the second gameObject is: "
		<< Vector2D<float>::SignedAngle(object1->GetPosition(), object2->GetPosition()) << std::endl;

	std::cout << "--------------------------------------------------------------\n" << std::endl;
	std::cout << "First Game Object Details:" << std::endl;
	std::cout << object1->ToString() << std::endl;

	std::cout << "Second Game Object Details:" << std::endl;
	std::cout << object2->ToString() << std::endl;
}



int main()
{
	// key is a string and the vaue is the game objects
	std::map<std::string, GameObject*> gameObjects;

	auto* ship = new GameObject("Ship", 0, 3.0f, 4.0f);
	auto* enemy = new GameObject("Enemy", 1, 10.0f, 20.0f);

	gameObjects[ship->GetName()] = ship;
	gameObjects[enemy->GetName()] = enemy;


	// for loop in every game object in gameObjets in loop

	for(const auto& game_object : gameObjects)
	{
		std::cout << "Key: " << game_object.first << std::endl;
		std::cout << "Value: " << std::endl;
		std::cout << "-------------------------------------------" << std::endl;
		std::cout <<game_object.second->ToString() << std::endl;

	}

	auto distance = Vector2D<float>::Distance(gameObjects["Ship"]->GetPosition(), gameObjects["Enemy"]->GetPosition());

	std::cout << "Distance between " << gameObjects["Ship"]->GetName()
		<< " and " << gameObjects["Enemy"]->GetName() << " is: " << std::to_string(distance) << "\n" << std::endl;

	std::ofstream outfile("GameObject.txt", std::ios::out);
	outfile << gameObjects["Ship"]->ToFile() << std::endl;
	outfile << gameObjects["Enemy"]->ToFile() << std::endl;

	outfile.close();
	

	std::ifstream infile;
	std::string fileName = "GameObject.txt";
	infile.open(fileName.c_str());

	if (infile.is_open())
	{
		int id;
		float x, y = 0;
		std::string name;
		Vector2D<float> position;

		while (!infile.fail())
		{


			infile >> ((id)) >> name;
			infile.ignore();
			infile >> x;
			infile.ignore();
			infile >> y;
			infile.ignore();

			auto* temp_object = new GameObject(name, id, x, y);

			gameObjects[name + "2"] = temp_object;
			

		}
		infile.close();
	}
	PrintGameObjects(gameObjects);
	std::cout << "------------------------------------------------------------------------------------------------\n";
	std::cout << " END OF INPUT \n";
	std::cout << "------------------------------------------------------------------------------------------------\n\n";

}

