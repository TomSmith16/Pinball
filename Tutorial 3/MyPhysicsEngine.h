#pragma once

#include "BasicActors.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	using namespace std;
	
	//a list of colours: Circus Palette
	static const PxVec3 color_palette[] = {
		PxVec3(0.f / 255.f, 0.f / 255.f, 75.f / 255.f),	//Floor
		PxVec3(10.f/255.f,10.f/255.f,50.f/255.f),		//Walls
		PxVec3(170.f/255.f,175.f/255.f,175.f/255.f),	//Ball
		PxVec3(255.f/255.f,45.f/255.f,0.f/255.f),		//Obstacles
		PxVec3(255.f/255.f,220.f/255.f,0.f/255.f),		//Bumpers
		PxVec3(4.f/255.f,117.f/255.f,111.f/255.f),		//Flippers

	};

	//pyramid vertices
	static PxVec3 pyramid_verts[] = {PxVec3(0,1,0), PxVec3(1,0,0), PxVec3(-1,0,0), PxVec3(0,0,1), PxVec3(0,0,-1)};
	//pyramid triangles: a list of three vertices for each triangle e.g. the first triangle consists of vertices 1, 4 and 0
	//vertices have to be specified in a counter-clockwise order to assure the correct shading in rendering
	static PxU32 pyramid_trigs[] = {1, 4, 0, 3, 1, 0, 2, 3, 0, 4, 2, 0, 3, 2, 1, 2, 4, 1};

	class Pyramid : public ConvexMesh
	{
	public:
		Pyramid(PxTransform pose=PxTransform(PxIdentity), PxReal density=1.f) :
			ConvexMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), pose, density)
		{
		}
	};

	class PyramidStatic : public TriangleMesh
	{
	public:
		PyramidStatic(PxTransform pose=PxTransform(PxIdentity)) :
			TriangleMesh(vector<PxVec3>(begin(pyramid_verts),end(pyramid_verts)), vector<PxU32>(begin(pyramid_trigs),end(pyramid_trigs)), pose)
		{
		}
	};

	struct FilterGroup
	{
		enum Enum
		{
			BALL		= (1 << 0),
			BUMPER		= (1 << 1),
			BUMPERSMALL	= (1 << 2),
			BUMPERWEDGE = (1 << 3),
			BATON		= (1 << 4),
			OBSTACLES	= (1 << 5),
			FLIPPERS	= (1 << 6),
			//add more if you need
		};
	};

	///An example class showing the use of springs (distance joints).
	class Trampoline
	{
		vector<DistanceJoint*> springs;
		Box *top;
		BoxStatic *bottom;

	public:
		Trampoline(const PxVec3& dimensions = PxVec3(1.7f, 3.5f, 1.f), PxReal stiffness = 1000.f, PxReal damping = 0.2f)
		{
			PxReal thickness = .8f;
			bottom = new BoxStatic(PxTransform(PxVec3(13.2f,PxReal(10.+thickness),29.f), PxQuat(-PxPiDivTwo, PxVec3(1.0f, 0.f, 0.f))),PxVec3(dimensions.x,thickness,dimensions.z));
			bottom->Color(color_palette[1]);
			top = new Box(PxTransform(PxVec3(13.2f, PxReal(dimensions.y+thickness+10.),26.f), PxQuat(-PxPiDivTwo, PxVec3(1.0f, 0.f, 0.f))),PxVec3(dimensions.x,thickness,dimensions.z));
			top->Color(color_palette[1]);
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(dimensions.x,-dimensions.y,-dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x,thickness,-dimensions.z)), top, PxTransform(PxVec3(-dimensions.x,-dimensions.y,-dimensions.z)));

			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
			}
		}

		void AddToScene(Scene* scene)
		{
			scene->Add(bottom);
			scene->Add(top);
		}

		void Prepare()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(2.0f);
				springs[i]->Damping(0.f);

			}
		}

		void Launch()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(1000.f);
				springs[i]->Damping(0.2f);

			}
		}

		~Trampoline()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}
	};



	class Plungeright
	{
		vector<DistanceJoint*> springs;
		Box *top;
		BoxStatic *bottom;

	public:
		Plungeright(const PxVec3& dimensions = PxVec3(.75f, 3.5f, .5f), PxReal stiffness = 1.5f, PxReal damping = 0.2f)
		{
			PxReal thickness = .4f;
			bottom = new BoxStatic(PxTransform(PxVec3(8.9f, PxReal(10.f + thickness), 29.f), PxQuat(-PxPiDivTwo, PxVec3(1.0f, 0.f, 0.f))), PxVec3(dimensions.x, thickness, dimensions.z));
			bottom->Color(color_palette[1]);
			top = new Box(PxTransform(PxVec3(8.9f, PxReal(dimensions.y + thickness + 10.f), 24.f), PxQuat(-PxPiDivTwo, PxVec3(1.0f, 0.f, 0.f))), PxVec3(dimensions.x, thickness, dimensions.z));
			top->Color(color_palette[1]);
			springs.resize(4);
			springs[0] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, dimensions.z)));
			springs[1] = new DistanceJoint(bottom, PxTransform(PxVec3(dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(dimensions.x, -dimensions.y, -dimensions.z)));
			springs[2] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, dimensions.z)));
			springs[3] = new DistanceJoint(bottom, PxTransform(PxVec3(-dimensions.x, thickness, -dimensions.z)), top, PxTransform(PxVec3(-dimensions.x, -dimensions.y, -dimensions.z)));

			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(stiffness);
				springs[i]->Damping(damping);
			}
		}

		void AddToScene(Scene* scene)
		{
			scene->Add(bottom);
			scene->Add(top);
		}

		void PrepareRight()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(2.0f);
				springs[i]->Damping(0.f);

			}
		}

		void LaunchRight()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
			{
				springs[i]->Stiffness(100.f);
				springs[i]->Damping(0.2f);

			}
		}

		void TurnTrigger()
		{
			top->SetTrigger(true);
			
			

		}

		~Plungeright()
		{
			for (unsigned int i = 0; i < springs.size(); i++)
				delete springs[i];
		}
	};

	///A customised collision class, implemneting various callbacks
	class MySimulationEventCallback : public PxSimulationEventCallback
	{
	public:
		//an example variable that will be checked in the main simulation loop
		bool tube, inspawn = true, dead, rightplunge = false, rightplungeblockbool = false, scored = false;
		string name, contactname;
		Scene* scene;
		PxScene *pxscene;
		int score = 0;
		//PhysicsEngine::MyScene *myscene;
		bool trigger;
		//PhysicsEngine::MyScene* scene2;
		
		
		MySimulationEventCallback() : trigger(false) {}

		///Method called when the contact with the trigger object is detected.
		virtual void onTrigger(PxTriggerPair* pairs, PxU32 count) 
		{
			//you can read the trigger information here
			for (PxU32 i = 0; i < count; i++)
			{
				//filter out contact with the planes
				if (pairs[i].otherShape->getGeometryType() != PxGeometryType::ePLANE)
				{
					//check if eNOTIFY_TOUCH_FOUND trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_FOUND && pairs[i].otherShape->getGeometryType() == PxGeometryType::eSPHERE)
					{



						//pxscene = pairs[i].triggerActor->getScene();
						name = pairs[i].triggerActor->getName();

						if (name == "Spawnblock")
						{
							inspawn = true;
						}

						//If dead, then lose a life and reset level
						if (name == "Deadzone")
						{

							cout << "Dead" << endl;
							dead = true;

						}
						
						//Check to see if ball is in spawn on the plunger
						if (name == "Plungertrigger")
						{
							inspawn = true;
							//cout << "Inspawn" << endl;
						}

						//Check if the right plunger has been fired, if so, increase points and block it off.
						if (name == "Rightplungertrigger")
						{
							//points = true;
							score = PointCounter(name, score);
							scored = true;
							rightplunge = true;
						}

						
						trigger = true;
						
						//cout << "Passed Spawn" << endl;
						//cerr << "onTrigger::eNOTIFY_TOUCH_FOUND" << endl;
						
					}
					//check if eNOTIFY_TOUCH_LOST trigger
					if (pairs[i].status & PxPairFlag::eNOTIFY_TOUCH_LOST && pairs[i].otherShape->getGeometryType() == PxGeometryType::eSPHERE)
					{
						
						//Bool to block spawn when the ball has left the trigger
						if (name == "Spawnblock")
						{
							inspawn = false;
							//cout << "Out of Spawn" << endl;
							
						}

						//Tube trigger to calculate points and spin the baton
						if (name == "Tubetrigger")
						{
							//points = true;
							score = PointCounter(name, score);
							scored = true;

							if (tube)
								tube = false;
							else
								tube = true;
						}

						//Check if the right plunger has been fired and needs blocking
						if (name == "Rightplungeblock")
						{
							if (!rightplungeblockbool && rightplunge)
								rightplungeblockbool = true;
								//scored = true;

						}

						//Trigger for points under the platform
						if (name == "Undertrigger")
						{
							score = PointCounter(name, score);
							scored = true;
						}
						//cerr << "onTrigger::eNOTIFY_TOUCH_LOST" << endl;
						trigger = false;

					}
				}
			}
		}

		///Method called when the contact by the filter shader is detected.
		virtual void onContact(const PxContactPairHeader &pairHeader, const PxContactPair *pairs, PxU32 nbPairs) 
		{
			//cerr << "Contact found between " << pairHeader.actors[0]->getName() << " " << pairHeader.actors[1]->getName() << endl;

			//check all pairs
			for (PxU32 i = 0; i < nbPairs; i++)
			{
				contactname = pairHeader.actors[0]->getName();
				//check eNOTIFY_TOUCH_FOUND
				//If contact is found
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_FOUND)
				{
					//Incrase the score based on name
					score = PointCounter(contactname, score);
					scored = true;
					//cerr << score << endl;
					//cerr << "onContact::eNOTIFY_TOUCH_FOUND" << endl;
				}
				//check eNOTIFY_TOUCH_LOST
				if (pairs[i].events & PxPairFlag::eNOTIFY_TOUCH_LOST)
				{
					//cerr << "onContact::eNOTIFY_TOUCH_LOST" << endl;
				}
			}
		}


		//Point calculating function based on Actor name, varying scores
		virtual int PointCounter(string name, int score)
		{
			if (name == "Mid1" || name == "Mid2" || name == "Mid3" || name == "Corner")
				score += 500;
				//cerr << score << endl;

			if (name == "Small1" || name == "Small2" || name == "Small3")
				score += 250;
				//cerr << score << endl;
			

			if (name == "Pointwedgel" || name == "Pointwedger")
				score += 350;
				//cerr << score << endl;
			


			if (name == "TopMid" || name == "TopL" || name == "TopR")
				score += 150;
				//cerr << score << endl;
			

			if (name == "Tubetrigger")
				score += 100;
			

			if (name == "Rightplungertrigger")
				score += 1000;

			if (name == "Baton" || name == "Undertrigger")
			{
				score += 50;
			}

			
			//cerr << "Score: " << score << endl;
			return score;
		}

		virtual void onConstraintBreak(PxConstraintInfo *constraints, PxU32 count) {}
		virtual void onWake(PxActor **actors, PxU32 count) {}
		virtual void onSleep(PxActor **actors, PxU32 count) {}
	};

	//A simple filter shader based on PxDefaultSimulationFilterShader - without group filtering
	static PxFilterFlags CustomFilterShader( PxFilterObjectAttributes attributes0,	PxFilterData filterData0,
		PxFilterObjectAttributes attributes1,	PxFilterData filterData1,
		PxPairFlags& pairFlags,	const void* constantBlock,	PxU32 constantBlockSize)
	{
		// let triggers through
		if(PxFilterObjectIsTrigger(attributes0) || PxFilterObjectIsTrigger(attributes1))
		{
			pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
			return PxFilterFlags();
		}

		pairFlags = PxPairFlag::eCONTACT_DEFAULT;
		//enable continous collision detection
		pairFlags |= PxPairFlag::eCCD_LINEAR;
		
		
		//customise collision filtering here
		//e.g.
		pairFlags = PxPairFlag::eSOLVE_CONTACT;
		pairFlags |= PxPairFlag::eDETECT_DISCRETE_CONTACT;
		pairFlags |= PxPairFlag::eDETECT_CCD_CONTACT;

		// trigger the contact callback for pairs (A,B) where 
		// the filtermask of A contains the ID of B and vice versa.
		if((filterData0.word0 & filterData1.word1) && (filterData1.word0 & filterData0.word1))
		{
			//trigger onContact callback for this pair of objects	
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_FOUND;
			pairFlags |= PxPairFlag::eNOTIFY_TOUCH_LOST;
			pairFlags |= PxPairFlag::eNOTIFY_CONTACT_POINTS;
		}

		return PxFilterFlags();
	};

	///Custom scene class
	class MyScene : public Scene
	{
		Plane* plane;
		Box* box, *box2,
			*obstacletopl, *obstacletopr, *obstacletopmid,
			*obstacletopthin1, *obstacletopthin2, *obstacletopthin3,
			*underplattrigger;
		Walls* walls, *glasswalls;
		
		Floor* table;
		MySimulationEventCallback* my_callback;
		GameWalls* gamewalls;
		RevoluteJoint* jointr, *jointl, *batonjoint;
		ConvexMesh* wedger, *wedgel, *pointwedgel, *pointwedger;
		
		Plungeright* plungeright;
		Deadzone* deadzone;
		Spawnblock* spawnblock;
		Capsule* mid1, *mid2, *mid3, *corner, *small1, *small2, *small3;
		PxMaterial* bumpers, *steelballbearing;
		Cornerwall* cornerwall;
		PlatformFloor* platformfloor;
		PlatformWalls *platformwalls;
		PlatformDrop* platformdrop;
		Box* baton, *glass, *rightplungeblock, *rightplungeblockobject;
		Tubetrigger* tubetrigger;
		Plungertrigger* plungertrigger, *rightplungertrigger;
	

		
	public:
		Sphere* ball;
		int lives = 3;
		Trampoline* plunger;
		bool trigger = false, spawnblockshow = false;
		int score2 = 0;
		int r1score = 0;
		int r2score = 0;
		int finalscore = 0;
		int highscore = 0;
		int nudgecounter = 0;
		bool tilt = false;
		MyScene() : Scene(CustomFilterShader) {};



		///A custom scene class
		void SetVisualisation()
		{
			px_scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
			px_scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
		}

		//Custom scene initialisation
		virtual void CustomInit() 
		{
			SetVisualisation();			

			px_scene->setGravity(PxVec3(0.f, -20.f, 8.f));

			//Creating the bouncy material, higher coefficient of restitution to repel ball faster than it hit them.
			bumpers = CreateMaterial(0.f, 0.f, 1.4f);

			//
			steelballbearing = CreateMaterial(0.f,0.f, 0.597f);

			//Set wall materials to similar friction and less restitution to stop insane bouncing off the walls,
			GetMaterial(0)->setDynamicFriction(.1f);
			GetMaterial(0)->setRestitution(.4f);
			///Initialise and set the customised event callback
			my_callback = new MySimulationEventCallback();
			px_scene->setSimulationEventCallback(my_callback);

			plane = new Plane();
			plane->Color(PxVec3(210.f/255.f,210.f/255.f,210.f/255.f));

			
			//Table floor
				table = new Floor(PxTransform(PxVec3(0.f, 10.f, 0.f)));	//, PxQuat(0.2f, PxVec3(1.f, 0.f, 0.f))  Rotating table
				table->Color(color_palette[0]);
				Add(table);

			//Boundaries
				walls = new Walls(PxTransform(PxVec3(0.f, 11.f, 0.f))); //, , PxQuat(0.2f, PxVec3(1.f, 0.f, 0.f))	Rotating walls
				walls->Color(color_palette[1]);
				//walls->SetKinematic(true);
				Add(walls);
			
			//Ball
				ball = new Sphere(PxTransform(PxVec3(13.2f, 10.f, 24.f)), 0.5f);
				ball->Color(color_palette[2]);
				ball->SetupFiltering(FilterGroup::BALL, FilterGroup::BUMPER | FilterGroup::BUMPERSMALL | FilterGroup:: BUMPERWEDGE | FilterGroup::BATON | FilterGroup::OBSTACLES);
				ball->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
				ball->Name("Ball");
				ball->Material(steelballbearing);
				ball->SetKinematic(true);
				Add(ball);

			//Paddles

				wedger = new ConvexMesh(
				{ PxVec3(3, 0, -.5), PxVec3(-2.5, 0, 0), PxVec3(3, 0, .5), PxVec3(-1.5, 0, -.5), PxVec3(-1.5, 0, .5),			PxVec3(-1.5, 1, .5), PxVec3(-1.5, 1, -.5), PxVec3(3, 1, .5), PxVec3(-2.5, 1, 0), PxVec3(3, 1, -.5) },
					PxTransform(PxVec3(6.f, 10.f, 22.f), PxQuat(PxPiDivFour, PxVec3(0.f,1.f,0.f)))); //Y = 5.2 for table at 0.2r rotation
				wedger->Color(color_palette[5]);
				wedger->SetupFiltering(FilterGroup::FLIPPERS, FilterGroup::BALL);
				

				jointr = new RevoluteJoint(nullptr, PxTransform(PxVec3(6.f, 9.5f, 22.f), PxQuat(PxPiDivTwo, PxVec3(0.f,0.f,1.f))), wedger, PxTransform(PxVec3(2.5f, 0.f, 0.f), PxQuat(PxPiDivTwo, PxVec3(0.0f,0.0f,1.f))));
				jointr->SetLimits(-PxPiDivFour, PxPiDivFour);
				Add(wedger);



				wedgel = new ConvexMesh(
				{ PxVec3(3, 0, -.5), PxVec3(4, 0, 0), PxVec3(3, 0, .5), PxVec3(-1.5, 0, -.5), PxVec3(-1.5, 0, .5),			PxVec3(-1.5, 1, .5), PxVec3(-1.5, 1, -.5), PxVec3(3, 1, .5), PxVec3(4, 1, 0), PxVec3(3, 1, -.5) },
					PxTransform(PxVec3(-6.f, 10.f, 22.f), PxQuat((-PxPiDivFour), PxVec3(0.f, 1.f, 0.f))));			//Y = 5.2 for table at 0.2r rotation
				wedgel->Color(color_palette[5]);
				wedgel->SetupFiltering(FilterGroup::FLIPPERS, FilterGroup::BALL);
				

				jointl = new RevoluteJoint(nullptr, PxTransform(PxVec3(-6.f, 9.5f, 22.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 0.f, 1.f))), wedgel, PxTransform(PxVec3(-1.f, 0.f, 0.f), PxQuat(PxPiDivTwo, PxVec3(0.0f, 0.0f, 1.f))));
				jointl->SetLimits(-PxPiDivFour, PxPiDivFour);
				Add(wedgel);

			//Baton in middle
				baton = new Box(PxTransform(PxVec3(-1.f, 10.f, 9.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))), PxVec3(1.5f, .5f, .5f));
				baton->Color(color_palette[3]);
				baton->Material(bumpers);
				baton->Name("Baton");
				baton->SetupFiltering(FilterGroup::BATON, FilterGroup::BALL);
				
				batonjoint = new RevoluteJoint(nullptr, PxTransform(PxVec3(-1.f, 10.f, 9.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 0.f, 1.f))), baton, PxTransform(PxVec3(0.f, 0.f, 0.f),PxQuat(PxPiDivTwo, PxVec3(0.0f, 0.0f, 1.f))));
				Add(baton);

			//Glass over the top of table if ball starts to fly out of the table
				glass = new Box(PxTransform(PxVec3(0.f, 14.5f, 0.f)), PxVec3(PxReal(30.f/1.89f), .25f, 30.f));
				glass->SetKinematic(true);
				glass->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				Add(glass);
				
				glasswalls = new Walls(PxTransform(PxVec3(0.f, 13.5f, 0.f)), PxVec3(30.f, .5f, .5f));
				glasswalls->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				glasswalls->GetShape(1)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				glasswalls->GetShape(2)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				glasswalls->GetShape(3)->setFlag(PxShapeFlag::eVISUALIZATION, false);

				
				Add(glasswalls);

				//Convex Meshes, make triangular shapes for paddles

				

			//Game over trigger
				deadzone = new Deadzone(PxTransform(PxVec3(-4.5f, 10.f, 28.f)));
				deadzone->SetTrigger(true);
				deadzone->SetKinematic(true);
				deadzone->GetShape(0)->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
				deadzone->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				deadzone->Name("Deadzone");

				Add(deadzone);



			//Block spawn trigger
				spawnblock = new Spawnblock(PxTransform(PxVec3(13.f, 10.f, -12.5f), PxQuat(PxPiDivFour, PxVec3(0.f, 1.f, 0.f))));
				spawnblock->SetTrigger(true);
				spawnblock->SetKinematic(true);
				spawnblock->Color(color_palette[1]);
				spawnblock->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				spawnblock->Name("Spawnblock");
				Add(spawnblock);
			

			//Tube Trigger
				tubetrigger = new Tubetrigger(PxTransform(-12.f, 11.5f, 11.f));
				tubetrigger->SetKinematic(true);
				tubetrigger->SetTrigger(true);
				tubetrigger->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				tubetrigger->Name("Tubetrigger");

				Add(tubetrigger);
					

			//Plunger and Right plunger
				plunger = new Trampoline();
				plunger->AddToScene(this);

				plungeright = new Plungeright();
				plungeright->AddToScene(this);


				rightplungertrigger = new Plungertrigger(PxTransform(PxVec3(9.f, 10.f, 27.5f)), PxVec3(1.5f, 1.5f, .5f));
				rightplungertrigger->SetKinematic(true);
				rightplungertrigger->SetTrigger(true);
				rightplungertrigger->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				rightplungertrigger->Name("Rightplungertrigger");
				Add(rightplungertrigger);

				rightplungeblock = new Box(PxTransform(PxVec3(8.7f, 10.f, 23.35f), PxQuat(PxPiDivFour/1.5, PxVec3(0.f, 1.f, 0.f))), PxVec3(2.5f, 1.5f, .5f));
				rightplungeblock->SetKinematic(true);
				rightplungeblock->SetTrigger(true);
				rightplungeblock->Color(color_palette[1]);

				rightplungeblock->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				
				rightplungeblock->Name("Rightplungeblock");
				Add(rightplungeblock);

				//Rightplungeblockobject
				rightplungeblockobject = new Box(PxTransform(PxVec3(8.7f, 10.f, 23.35f), PxQuat(PxPiDivFour/1.5, PxVec3(0.f, 1.f, 0.f))), PxVec3(2.5f, 1.5f, .5f));
				rightplungeblockobject->SetKinematic(true);
				rightplungeblockobject->Color(color_palette[1]);
				//rightplungeblockobject->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);

				plungertrigger = new Plungertrigger(PxTransform(PxVec3(13.2f, 10.f, 25.f)));
				plungertrigger->SetKinematic(true);
				plungertrigger->SetTrigger(true);
				plungertrigger->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				plungertrigger->Name("Plungertrigger");
				Add(plungertrigger);



				underplattrigger = new Box(PxTransform(PxVec3(-13.5f, 10.f, 3.f), PxQuat(PxPiDivFour, PxVec3(0.f, 1.f, 0.f))), PxVec3(1.5f, .5f, 2.f));
				underplattrigger->SetKinematic(true);
				underplattrigger->SetTrigger(true);
				underplattrigger->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				underplattrigger->Name("Undertrigger");
				Add(underplattrigger);
				//Damping and stiffness alterations in Launch() and Prepare() on keypress to create plunger effect
			

			//In Game Walls
				gamewalls = new GameWalls(PxTransform(PxVec3(0.f, 1.f, 0.f)));
				gamewalls->SetKinematic(true);
				gamewalls->Color(color_palette[1]);
				Add(gamewalls);


				//Platform
				platformfloor = new PlatformFloor(PxTransform(PxVec3(0.f, 0.f, 0.f)));
				platformfloor->SetKinematic(true);
				platformfloor->Color(color_palette[0]);
				Add(platformfloor);

				//PlatformWalls
				platformwalls = new PlatformWalls(PxTransform(PxVec3(0.f, 1.f, 0.f)));
				platformwalls->SetKinematic(true);
				platformwalls->Color(color_palette[1]);
				Add(platformwalls);

				//PlatformDrop
				platformdrop = new PlatformDrop(PxTransform(PxVec3(-12.f, 0.f, 11.f)));
				platformdrop->SetKinematic(true);
				platformdrop->Color(color_palette[3]);
				Add(platformdrop);

				


			//Top obstacles
				obstacletopl = new Box(PxTransform(PxVec3(-5.f, 10.f, -19.f), PxQuat(PxPiDivFour / 2, PxVec3(0.f, 1.f, 0.f))), PxVec3(1.6f, .5f, .25f));
				obstacletopl->SetKinematic(true);
				obstacletopl->Material(bumpers);
				obstacletopl->Color(color_palette[3]);
				obstacletopl->SetupFiltering(FilterGroup::OBSTACLES, FilterGroup::BALL);
				obstacletopl->Name("TopL");

				Add(obstacletopl);


				obstacletopr = new Box(PxTransform(PxVec3(5.f, 10.f, -19.f), PxQuat(-PxPiDivFour / 2, PxVec3(0.f, 1.f, 0.f))), PxVec3(1.6f, .5f, .25f));
				obstacletopr->SetKinematic(true);
				obstacletopr->Material(bumpers);
				obstacletopr->Color(color_palette[3]);
				obstacletopr->SetupFiltering(FilterGroup::OBSTACLES, FilterGroup::BALL);
				obstacletopr->Name("TopR");

				Add(obstacletopr);


				obstacletopmid = new Box(PxTransform(PxVec3(-.3f, 10.f, -4.2f), PxQuat(-PxPiDivFour / 2, PxVec3(0.f, 1.f, 0.f))), PxVec3(1.2f, .5f, .25f));
				obstacletopmid->SetKinematic(true);
				obstacletopmid->Material(bumpers);
				obstacletopmid->Color(color_palette[3]);
				obstacletopmid->SetupFiltering(FilterGroup::OBSTACLES, FilterGroup::BALL);
				obstacletopmid->Name("TopMid");
				
				Add(obstacletopmid);


				obstacletopthin1 = new Box(PxTransform(PxVec3(2.f, 10.f, -19.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))), PxVec3(.5f, .5f, .25f));
				obstacletopthin1->SetKinematic(true);
				obstacletopthin1->Color(color_palette[3]);
				Add(obstacletopthin1);

				obstacletopthin2 = new Box(PxTransform(PxVec3(0.f, 10.f, -19.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))), PxVec3(.5f, .5f, .25f));
				obstacletopthin2->SetKinematic(true);
				obstacletopthin2->Color(color_palette[3]);
				Add(obstacletopthin2);

				obstacletopthin3 = new Box(PxTransform(PxVec3(-2.f, 10.f, -19.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))), PxVec3(.5f, .5f, .25f));
				obstacletopthin3->SetKinematic(true);
				obstacletopthin3->Color(color_palette[3]);
				Add(obstacletopthin3);

			//Point scoring bumpers
				mid1 = new Capsule(PxTransform(PxVec3(3.f, 10.f, -10.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 0.f, 1.f))),PxVec2(1.f, .5f));
				mid1->SetKinematic(true);
				mid1->Material(bumpers);
				mid1->SetupFiltering(FilterGroup::BUMPER, FilterGroup::BALL);
				mid1->Name("Mid1");
				mid1->Color(color_palette[4]);
				mid1->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
				Add(mid1);

				mid2 = new Capsule(PxTransform(PxVec3(-3.f, 10.f, -10.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 0.f, 1.f))), PxVec2(1.f, .5f));
				mid2->SetKinematic(true);
				mid2->Material(bumpers);
				mid2->SetupFiltering(FilterGroup::BUMPER, FilterGroup::BALL);
				mid2->Name("Mid2");
				mid2->Color(color_palette[4]);
				mid2->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
				Add(mid2);

				mid3 = new Capsule(PxTransform(PxVec3(0.f, 10.f, -6.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 0.f, 1.f))), PxVec2(1.f, .5f));
				mid3->SetKinematic(true);
				mid3->Material(bumpers);
				mid3->SetupFiltering(FilterGroup::BUMPER, FilterGroup::BALL);
				mid3->Name("Mid3");
				mid3->Color(color_palette[4]);
				mid3->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
				Add(mid3);

				corner = new Capsule(PxTransform(PxVec3(-11.f, 10.f, -23.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 0.f, 1.f))), PxVec2(1.f, .5f));
				corner->SetKinematic(true);
				corner->Material(bumpers);
				corner->Color(color_palette[4]);
				corner->SetupFiltering(FilterGroup::BUMPER, FilterGroup::BALL);
				corner->Name("Corner");
				Add(corner);

				small1 = new Capsule(PxTransform(PxVec3(-11.f, 11.65f, 4.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 0.f, 1.f))), PxVec2(.5f, .5f));
				small1->SetKinematic(true);
				small1->Material(bumpers);
				small1->Color(color_palette[4]);
				small1->SetupFiltering(FilterGroup::BUMPERSMALL, FilterGroup::BALL);
				small1->Name("Small1");
				Add(small1);

				small2 = new Capsule(PxTransform(PxVec3(-13.f, 11.65f, 4.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 0.f, 1.f))), PxVec2(.5f, .5f));
				small2->SetKinematic(true);
				small2->Material(bumpers);
				small2->Color(color_palette[4]);
				small2->SetupFiltering(FilterGroup::BUMPERSMALL, FilterGroup::BALL);
				small2->Name("Small2");
				Add(small2);

				small3 = new Capsule(PxTransform(PxVec3(-12.f, 11.65f, 7.f), PxQuat(PxPiDivTwo, PxVec3(0.f, 0.f, 1.f))), PxVec2(.5f, .5f));
				small3->SetKinematic(true);
				small3->Material(bumpers);
				small3->Color(color_palette[4]);
				small3->SetupFiltering(FilterGroup::BUMPERSMALL, FilterGroup::BALL);
				small3->Name("Small3");
				Add(small3);

				pointwedgel = new ConvexMesh({ PxVec3(-3.f, 0.f, -3.f), PxVec3(-3.f, 0.f, 0.f), PxVec3(-1.f, 0.f, 2.f),  PxVec3(-3.f, 1.f, -3.f), PxVec3(-3.f, 1.f, 0.f), PxVec3(-1.f, 1.f, 2.f) },
					PxTransform(PxVec3(-5.f, 10.f, 17.5f)));
				pointwedgel->SetKinematic(true);
				pointwedgel->Material(bumpers);
				pointwedgel->Name("Pointwedgel");
				pointwedgel->Color(color_palette[3]);
				pointwedgel->SetupFiltering(FilterGroup::BUMPERWEDGE, FilterGroup::BALL);
				Add(pointwedgel);

				pointwedger = new ConvexMesh({ PxVec3(-3.f, 0.f, -3.f), PxVec3(-3.f, 0.f, 0.f), PxVec3(-1.f, 0.f, 2.f),  PxVec3(-3.f, 1.f, -3.f), PxVec3(-3.f, 1.f, 0.f), PxVec3(-1.f, 1.f, 2.f) },
					PxTransform(PxVec3(5.f, 11.f, 17.5f), PxQuat(PxPi, PxVec3(0.f, 0.f, 1.f))));
				pointwedger->SetKinematic(true);
				pointwedger->Material(bumpers);
				pointwedger->Name("Pointwedger");
				pointwedger->Color(color_palette[3]);
				pointwedger->SetupFiltering(FilterGroup::BUMPERWEDGE, FilterGroup::BALL);
				Add(pointwedger);


			//Tilt function

			/*
			//joint two boxes together
			//the joint is fixed to the centre of the first box, oriented by 90 degrees around the Y axis
			//and has the second object attached 5 meters away along the Y axis from the first object.
			RevoluteJoint joint(box, PxTransform(PxVec3(0.f,0.f,0.f),PxQuat(PxPi/2,PxVec3(0.f,1.f,0.f))), box2, PxTransform(PxVec3(0.f,5.f,0.f)));
			*/
		}

		//Custom udpate function
		virtual void CustomUpdate() 
		{
			//If the scored boolean is true, increase and display points.
			if(my_callback->scored)
			{
				score2 = my_callback->score;
				if(lives == 3)
					cerr << "SCORE:" << score2 << endl;
				else if (lives == 2)
					cerr << "SCORE:" << score2 + r1score << endl;
				else if (lives == 1)
					cerr << "SCORE:" << r2score + score2 << endl;


				my_callback->scored = false;
			}

			//If through tube trigger, reverse direction of baton.
			if (!my_callback->tube)
				batonjoint->DriveVelocity(15.f);
			else
				batonjoint->DriveVelocity(-15.f);


			//If in spawn, unblock the exit
			if (my_callback->inspawn)
			{
				//spawnblock->SetTrigger(true);
				spawnblock->GetShape(0)->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
				spawnblock->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
				spawnblock->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, false);
				
			}
			else
			{
				//spawnblock->SetTrigger(false);
				spawnblock->GetShape(0)->setFlag(PxShapeFlag::eTRIGGER_SHAPE, false);
				spawnblock->GetShape(0)->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
				spawnblock->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, true);
			}

			//If dead, reset the level and display points.
			if (my_callback->dead)
			{
				nudgecounter = 0;
				tilt = false;
				if (lives > 0)
				{
					lives -= 1;
					if(lives == 2)
					{
						r1score = score2;
						cerr << "END OF R1: " << r1score << endl;
					}
					else if (lives == 1)
					{
						r2score = score2 + r1score;
						cerr << "END OF R2: " << r2score << endl;
					}
					finalscore = r2score + score2;
					score2 = 0;
					this->Reset();
					my_callback->dead = false;
				}

				cout << "Lives: " << lives << endl;
			}

			//If game over
			if (lives == 0)
			{
				//finalscore = r2score + score2;
				if (finalscore > highscore)
				{
					highscore = finalscore;
				}
				cerr << "FINAL SCORE: " << finalscore << endl;
				cerr << "Thanks for playing! Press ESC to quit or # to play again!" << endl;
				lives = 3;
			}

			//Launch plunger if the ball touches it
			if (my_callback->rightplunge)
			{
				
				plungeright->LaunchRight();
				
			}
				
			//Block the right plunger if it's been fired.
			if (my_callback->rightplunge && my_callback->rightplungeblockbool)
			{
				plungeright->TurnTrigger();
				rightplungeblockobject->GetShape(0)->setFlag(PxShapeFlag::eVISUALIZATION, true);
				this->Add(rightplungeblockobject);
				my_callback->rightplunge = false;

			}
			
			

		}

		//attempt to update scoring hud on visual debugger
		int ScoringHUD()
		{
			if(lives == 3)
				return score2;
			else if (lives == 2)
				return r1score + score2;
			else if (lives == 1)
				return r2score+score2;
			else 
			return 0;

		}

		/// An example use of key release handling
		void LeftFlipperRelease()
		{
			jointl->DriveVelocity(PxReal(-15));
			
		}

		/// An example use of key presse handling
		void LeftFlipperPress()
		{
			jointl->DriveVelocity(PxReal(15));
			//cerr << "I am pressed!" << endl;
			
		}

		void RightFlipperRelease()
		{
			jointr->DriveVelocity(PxReal(15));

		}

		/// An example use of key presse handling
		void RightFlipperPress()
		{
			jointr->DriveVelocity(PxReal(-15));
			//cerr << "I am pressed!" << endl;

		}




	};
}
