#pragma once

#include "PhysicsEngine.h"
#include <iostream>
#include <iomanip>

namespace PhysicsEngine
{
	///Plane class
	class Plane : public StaticActor
	{
	public:
		//A plane with default paramters: XZ plane centred at (0,0,0)
		Plane(PxVec3 normal=PxVec3(0.f, 1.f, 0.f), PxReal distance=0.f) 
			: StaticActor(PxTransformFromPlaneEquation(PxPlane(normal, distance)))
		{
			CreateShape(PxPlaneGeometry());
		}
	};

	///Sphere class
	class Sphere : public DynamicActor
	{
	public:
		//a sphere with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m
		// - denisty: 1kg/m^3
		Sphere(const PxTransform& pose=PxTransform(PxIdentity), PxReal radius=1.f, PxReal density=1.f) 
			: DynamicActor(pose)
		{ 
			CreateShape(PxSphereGeometry(radius), density);
		}
	};

	///Box class
	class Box : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Box(const PxTransform& pose=PxTransform(PxIdentity), PxVec3 dimensions=PxVec3(.5f,.5f,.5f), PxReal density=1.f) 
			: DynamicActor(pose)
		{ 
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	class PlatformFloor : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		PlatformFloor(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			//ramp
			CreateShape(PxBoxGeometry(PxVec3(2.f, .2f, 5.f)), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(-11.5f, 10.f, -5.f), PxQuat(-PxPiDivFour / 3, PxVec3(1.f, 0.f, 0.f))));

			//platform
			CreateShape(PxBoxGeometry(PxVec3(3.f, .2f, 5.2f)), density);
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-11.8f, 11.25f, 4.95f)));


		}
	};

	class PlatformWalls : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		PlatformWalls(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f)
			: DynamicActor(pose)
		{


			//rampwallr
			CreateShape(PxBoxGeometry(PxVec3(.25f, .25f, 5.f)), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(-13.5f, 9.5f, -4.6f), PxQuat(-PxPiDivFour / 3, PxVec3(1.f, 0.f, 0.f))));

			//rampwalll
			CreateShape(PxBoxGeometry(PxVec3(.25f, .25f, 5.f)), density);
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-9.5f, 9.5f, -4.6f), PxQuat(-PxPiDivFour / 3, PxVec3(1.f, 0.f, 0.f))));



			//platformwalll
			CreateShape(PxBoxGeometry(PxVec3(.25f, 1.25f, 1.5f)), density);
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-14.f, 11.75f, 8.3f), PxQuat(PxPiDivFour, PxVec3(0.0f, 1.f, 0.f))));

			//platformwallr
			CreateShape(PxBoxGeometry(PxVec3(.25f, 1.25f, 1.7f)), density);
			GetShape(3)->setLocalPose(PxTransform(PxVec3(-10.f, 11.75f, 8.3f), PxQuat(-PxPiDivFour, PxVec3(0.0f, 1.f, 0.f))));

			//platformedge
			CreateShape(PxBoxGeometry(PxVec3(.25f, 1.f, 3.5f)), density);
			GetShape(4)->setLocalPose(PxTransform(PxVec3(-8.7f, 11.75f, 3.5f)));

			//platformedge1
			CreateShape(PxBoxGeometry(PxVec3(.25f, 1.f, .5f)), density);
			GetShape(5)->setLocalPose(PxTransform(PxVec3(-9.f, 11.5f, 0.1f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))));

			//platformedge2
			CreateShape(PxBoxGeometry(PxVec3(.25f, 1.f, 1.f)), density);
			GetShape(6)->setLocalPose(PxTransform(PxVec3(-14.5f, 11.5f, 0.1f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))));
		}
	};

	class PlatformDrop : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		PlatformDrop(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .25f, .25f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(PxVec3(dimensions.x+ 0.25f, dimensions.y+0.5f, dimensions.z)), density);
			CreateShape(PxBoxGeometry(PxVec3(dimensions.x + 0.75f, dimensions.y + 0.5f, dimensions.z)), density);
			CreateShape(PxBoxGeometry(PxVec3(dimensions.x + 0.75f, dimensions.y + 0.5f, dimensions.z)), density);
			CreateShape(PxBoxGeometry(PxVec3(dimensions.x, dimensions.y, dimensions.z)), density);

			GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, 11.25f, 0.8f)));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(0.95f, 11.25f, -0.5f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(-.95f, 11.25f, -0.5f), PxQuat(-PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(0.f, 11.f, -.8f), PxQuat(PxPiDivFour / 4, PxVec3(1.f, 0.f, 0.f))));


		}

	};

	class BoxStatic : public StaticActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		BoxStatic(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};
	//Attempt at making a curve
	class Cornerwall : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Cornerwall(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(.5f, .5f, .5f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);

			/*GetShape(0)->setLocalPose(PxTransform(PxVec3(0.f, 0.f, 20.f), PxQuat(0.3, PxVec3(0.f, 1.f, 0.f))));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(.8f, 0.f, 19.6f),PxQuat(0.7, PxVec3(0.f, 1.f, 0.f))));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(1.2f, 0.f, 19.2f), PxQuat(1.1, PxVec3(0.f, 1.f, 0.f))));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(1.4f, 0.f, 18.8f), PxQuat(1.5, PxVec3(0.f, 1.f, 0.f))));
			GetShape(4)->setLocalPose(PxTransform(PxVec3(1.45f, 0.f, 18.2f), PxQuat(1.9, PxVec3(0.f, 1.f, 0.f))));
			GetShape(5)->setLocalPose(PxTransform(PxVec3(1.4f, 0.f, 17.8f), PxQuat(2.3, PxVec3(0.f, 1.f, 0.f))));
			GetShape(6)->setLocalPose(PxTransform(PxVec3(1.1f, 0.f, 17.5f), PxQuat(2.5, PxVec3(0.f, 1.f, 0.f))));
			GetShape(7)->setLocalPose(PxTransform(PxVec3(.7f, 0.f, 17.2f), PxQuat(2.6, PxVec3(0.f, 1.f, 0.f))));*/
		}
	};

	class Deadzone : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Deadzone(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(12.f, 1.f, 1.f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	class GameWalls : public DynamicActor
	{
		public:
			//a Box with default parameters:
			// - pose in 0,0,0
			// - dimensions: 1m x 1m x 1m
			// - denisty: 1kg/m^3
			GameWalls(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(12.f, 1.f, 1.f), PxReal density = 1.f)
				: DynamicActor(pose)
			{

				//Ingame walls


				//plungerwall
				CreateShape(PxBoxGeometry(PxVec3(.8f, 2.5f, 20.f)), density);
				GetShape(0)->setLocalPose(PxTransform(PxVec3(10.5f, 10.f, 10.f)));

				//toprightcorner


				CreateShape(PxBoxGeometry(PxVec3(10.f, 2.5f, .5f)), density);
				GetShape(1)->setLocalPose(PxTransform(PxVec3(8.3f, 10.f, -23.f), PxQuat(-PxPiDivFour, PxVec3(0.f, 1.f, 0.f))));

				//topleftcorner
	

				CreateShape(PxBoxGeometry(PxVec3(5.f, 2.5f, .5f)), density);
				GetShape(2)->setLocalPose(PxTransform(PxVec3(-12.3f, 10.f, -27.f), PxQuat(PxPiDivFour, PxVec3(0.f, 1.f, 0.f))));

				//barrierleft
	

				CreateShape(PxBoxGeometry(PxVec3(3.5f, 2.5f, .5f)), density);
				GetShape(3)->setLocalPose(PxTransform(PxVec3(-9.5f, 10.f, 20.f), PxQuat(-PxPiDivFour / 2, PxVec3(0.0f, 1.f, 0.f))));

				//barrierright

	

				CreateShape(PxBoxGeometry(PxVec3(1.f, 2.5f, .5f)), density);
				GetShape(4)->setLocalPose(PxTransform(PxVec3(7.f, 10.f, 21.f), PxQuat(PxPiDivFour / 2, PxVec3(0.0f, 1.f, 0.f))));

				//Left gap


				CreateShape(PxBoxGeometry(PxVec3(3.f, 2.5f, .25f)), density);
				GetShape(5)->setLocalPose(PxTransform(PxVec3(-12.7f, 10.f, 17.2f), PxQuat(PxPiDivTwo, PxVec3(0.0f, 1.f, 0.f))));



				CreateShape(PxBoxGeometry(PxVec3(4.f, 2.5f, .5f)), density);
				GetShape(6)->setLocalPose(PxTransform(PxVec3(-12.f, 10.f, 23.f), PxQuat(-PxPiDivFour / 2, PxVec3(0.0f, 1.f, 0.f))));



				CreateShape(PxBoxGeometry(PxVec3(1.f, 2.5f, .25f)), density);
				GetShape(7)->setLocalPose(PxTransform(PxVec3(-7.8f, 10.f, 25.1f), PxQuat(-PxPiDivTwo / 1.5, PxVec3(0.0f, 1.f, 0.f))));



				//Right gap


				CreateShape(PxBoxGeometry(PxVec3(.5f, 2.5f, .25f)), density);
				GetShape(8)->setLocalPose(PxTransform(PxVec3(7.5f, 10.f, 20.5f), PxQuat(PxPiDivFour/1.5, PxVec3(0.0f, 1.f, 0.f))));


				CreateShape(PxBoxGeometry(PxVec3(.5f, 2.5f, 2.5f)), density);
				GetShape(9)->setLocalPose(PxTransform(PxVec3(7.5f, 10.f, 27.5f)));




				CreateShape(PxBoxGeometry(PxVec3(1.f, 2.5f, .25f)), density);
				GetShape(10)->setLocalPose(PxTransform(PxVec3(5.7f, 10.f, 25.8f), PxQuat(PxPiDivTwo / 1.5, PxVec3(0.0f, 1.f, 0.f))));



				//Under Platform


				CreateShape(PxBoxGeometry(PxVec3(.5f, .5f, 4.f)), density);
				GetShape(11)->setLocalPose(PxTransform(PxVec3(-12.5f, 9.f, 7.f), PxQuat(PxPiDivFour, PxVec3(0.f, 1.f, 0.f))));

		

				CreateShape(PxBoxGeometry(PxVec3(.5f, .5f, 2.f)), density);
				GetShape(12)->setLocalPose(PxTransform(PxVec3(-10.5f, 9.f, 3.f), PxQuat(PxPiDivFour, PxVec3(0.f, 1.f, 0.f))));



				CreateShape(PxBoxGeometry(PxVec3(.5f, .5f, 2.5f)), density);
				GetShape(13)->setLocalPose(PxTransform(PxVec3(-12.25f, 9.f, -.5f), PxQuat(PxReal(PxPiDivFour / 4), PxVec3(0.f, 1.f, 0.f))));


				//Right side

				CreateShape(PxBoxGeometry(PxVec3(3.f, 2.5f, .5f)), density);
				GetShape(14)->setLocalPose(PxTransform(PxVec3(8.f, 10.f, 2.f), PxQuat(PxPiDivFour, PxVec3(0.f, 1.f, 0.f))));


				CreateShape(PxBoxGeometry(PxVec3(1.5f, 2.5f, .5f)), density);
				GetShape(15)->setLocalPose(PxTransform(PxVec3(6.f, 10.f, 5.3f), PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, 0.f))));


				CreateShape(PxBoxGeometry(PxVec3(3.f, 2.5f, .5f)), density);
				GetShape(16)->setLocalPose(PxTransform(PxVec3(8.f, 10.f, 9.f), PxQuat(-PxPiDivFour, PxVec3(0.f, 1.f, 0.f))));

				//bonus right gap
				CreateShape(PxBoxGeometry(PxVec3(.5f, 2.5f, 1.f)), density);
				GetShape(17)->setLocalPose(PxTransform(PxVec3(7.f, 10.f, 25.f), PxQuat(PxPiDivTwo/1.5, PxVec3(0.f, 1.f, 0.f))));

				//bonus under platform reflector

				CreateShape(PxBoxGeometry(PxVec3(.5f, .5f, 2.5f)), density);
				GetShape(18)->setLocalPose(PxTransform(PxVec3(-13.25f, 9.f, 10.f), PxQuat(-PxPiDivTwo/1.5, PxVec3(0.f,1.f,0.f))));

				CreateShape(PxBoxGeometry(PxVec3(.5f, .5f, 4.f)), density);
				GetShape(19)->setLocalPose(PxTransform(PxVec3(-9.5f, 9.f, 0.f)));

			}
	};

	class Spawnblock : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Spawnblock(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(3.5f, 2.5f, 1.f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	class Tubetrigger : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Tubetrigger(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(1.f, .25f, 1.f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	class Plungertrigger : public DynamicActor
	{
	public:
		//a Box with default parameters:
		// - pose in 0,0,0
		// - dimensions: 1m x 1m x 1m
		// - denisty: 1kg/m^3
		Plungertrigger(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(1.5f, .5f, .5f), PxReal density = 1.f)
			: DynamicActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
		}
	};

	class Walls : public StaticActor {
	public: 
		Walls(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(30.f, 2.5f, .5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(dimensions), density);
			CreateShape(PxBoxGeometry(PxReal(dimensions.x / 1.89), dimensions.y, dimensions.z), density);
			CreateShape(PxBoxGeometry(PxReal(dimensions.x/1.89), dimensions.y, dimensions.z), density);
			
			

			GetShape(0)->setLocalPose(PxTransform(PxVec3(15.5f, .0f, 0.f), (PxQuat(PxPiDivTwo, PxVec3(0.f, 1.f, .0f)))));
			GetShape(1)->setLocalPose(PxTransform(PxVec3(-15.5f, .0f, 0.f), (PxQuat(-PxPiDivTwo, PxVec3(0.f, 1.f, .0f)))));
			GetShape(2)->setLocalPose(PxTransform(PxVec3(.0f, .0f, 30.5f), (PxQuat(PxPi, PxVec3(0.f, 1.f, .0f)))));
			GetShape(3)->setLocalPose(PxTransform(PxVec3(.0f, .0f, -30.5f), (PxQuat(-PxPi, PxVec3(0.f, 1.f, .0f)))));

			


		}
	};

	class Floor : public StaticActor {
	public:
		Floor(const PxTransform& pose = PxTransform(PxIdentity), PxVec3 dimensions = PxVec3(30.f, .5f, .5f), PxReal density = 1.f)
			: StaticActor(pose)
		{
			CreateShape(PxBoxGeometry(PxReal(dimensions.x / 1.89), dimensions.y, PxReal(dimensions.z * 60)), density);
			GetShape(0)->setLocalPose(PxTransform(PxVec3(.0f, -1.f, .0f)));
		}
	};

	class Capsule : public DynamicActor
	{
	public:
		Capsule(const PxTransform& pose=PxTransform(PxIdentity), PxVec2 dimensions=PxVec2(1.f,1.f), PxReal density=1.f) 
			: DynamicActor(pose)
		{
			CreateShape(PxCapsuleGeometry(dimensions.x, dimensions.y), density);
		}
	};


	///The ConvexMesh class
	class ConvexMesh : public DynamicActor
	{
	public:
		//constructor
		ConvexMesh(const std::vector<PxVec3>& verts, const PxTransform& pose=PxTransform(PxIdentity), PxReal density=1.f)
			: DynamicActor(pose)
		{
			PxConvexMeshDesc mesh_desc;
			mesh_desc.points.count = (PxU32)verts.size();
			mesh_desc.points.stride = sizeof(PxVec3);
			mesh_desc.points.data = &verts.front();
			mesh_desc.flags = PxConvexFlag::eCOMPUTE_CONVEX;
			mesh_desc.vertexLimit = 256;

			CreateShape(PxConvexMeshGeometry(CookMesh(mesh_desc)), density);
		}

		//mesh cooking (preparation)
		PxConvexMesh* CookMesh(const PxConvexMeshDesc& mesh_desc)
		{
			PxDefaultMemoryOutputStream stream;

			if(!GetCooking()->cookConvexMesh(mesh_desc, stream))
				throw new Exception("ConvexMesh::CookMesh, cooking failed.");

			PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

			return GetPhysics()->createConvexMesh(input);
		}
	};

	///The TriangleMesh class
	class TriangleMesh : public StaticActor
	{
	public:
		//constructor
		TriangleMesh(const std::vector<PxVec3>& verts, const std::vector<PxU32>& trigs, const PxTransform& pose=PxTransform(PxIdentity))
			: StaticActor(pose)
		{
			PxTriangleMeshDesc mesh_desc;
			mesh_desc.points.count = (PxU32)verts.size();
			mesh_desc.points.stride = sizeof(PxVec3);
			mesh_desc.points.data = &verts.front();
			mesh_desc.triangles.count = (PxU32)trigs.size();
			mesh_desc.triangles.stride = 3*sizeof(PxU32);
			mesh_desc.triangles.data = &trigs.front();

			CreateShape(PxTriangleMeshGeometry(CookMesh(mesh_desc)));
		}

		//mesh cooking (preparation)
		PxTriangleMesh* CookMesh(const PxTriangleMeshDesc& mesh_desc)
		{
			PxDefaultMemoryOutputStream stream;

			if(!GetCooking()->cookTriangleMesh(mesh_desc, stream))
				throw new Exception("TriangleMesh::CookMesh, cooking failed.");

			PxDefaultMemoryInputData input(stream.getData(), stream.getSize());

			return GetPhysics()->createTriangleMesh(input);
		}
	};

	//Distance joint with the springs switched on
	class DistanceJoint : public Joint
	{
	public:
		DistanceJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = (PxJoint*)PxDistanceJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION, true);
			((PxDistanceJoint*)joint)->setDistanceJointFlag(PxDistanceJointFlag::eSPRING_ENABLED, true);
			Damping(1.f);
			Stiffness(1.f);
		}

		void Stiffness(PxReal value)
		{
			((PxDistanceJoint*)joint)->setStiffness(value);
		}

		PxReal Stiffness()
		{
			return ((PxDistanceJoint*)joint)->getStiffness();		
		}

		void Damping(PxReal value)
		{
			((PxDistanceJoint*)joint)->setDamping(value);
		}

		PxReal Damping()
		{
			return ((PxDistanceJoint*)joint)->getDamping();
		}
	};

	///Revolute Joint
	class RevoluteJoint : public Joint
	{
	public:
		RevoluteJoint(Actor* actor0, const PxTransform& localFrame0, Actor* actor1, const PxTransform& localFrame1)
		{
			PxRigidActor* px_actor0 = 0;
			if (actor0)
				px_actor0 = (PxRigidActor*)actor0->Get();

			joint = PxRevoluteJointCreate(*GetPhysics(), px_actor0, localFrame0, (PxRigidActor*)actor1->Get(), localFrame1);
			joint->setConstraintFlag(PxConstraintFlag::eVISUALIZATION,true);
		}

		void DriveVelocity(PxReal value)
		{
			//wake up the attached actors
			PxRigidDynamic *actor_0, *actor_1;
			((PxRevoluteJoint*)joint)->getActors((PxRigidActor*&)actor_0, (PxRigidActor*&)actor_1);
			if (actor_0)
			{
				if (actor_0->isSleeping())
					actor_0->wakeUp();
			}
			if (actor_1)
			{
				if (actor_1->isSleeping())
					actor_1->wakeUp();
			}
			((PxRevoluteJoint*)joint)->setDriveVelocity(value);
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eDRIVE_ENABLED, true);
		}

		PxReal DriveVelocity()
		{
			return ((PxRevoluteJoint*)joint)->getDriveVelocity();
		}

		void SetLimits(PxReal lower, PxReal upper)
		{
			((PxRevoluteJoint*)joint)->setLimit(PxJointAngularLimitPair(lower, upper));
			((PxRevoluteJoint*)joint)->setRevoluteJointFlag(PxRevoluteJointFlag::eLIMIT_ENABLED, true);
		}
	};
}