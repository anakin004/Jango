#include "cnpch.h"
#include "Physics3D.h"
#include "PxPhysicsAPI.h"


namespace Crimson {
	physx::PxFoundation* Physics3D::m_foundation = nullptr;
	physx::PxPhysics* Physics3D::m_physics = nullptr;
	physx::PxCudaContextManager* Physics3D::gCudaContextManager = nullptr;
	physx::PxScene* Physics3D::m_scene = nullptr;
	physx::PxDefaultCpuDispatcher* Physics3D::m_dispatcher = nullptr;
	physx::PxMaterial* Physics3D::m_defaultMaterial = nullptr;
	physx::PxRigidDynamic* Physics3D::m_boxActor = nullptr;
	physx::PxRigidStatic* Physics3D::m_groundActor = nullptr;
	std::vector<physx::PxRigidDynamic*> Physics3D::m_RigidDynamic_arr;
	std::vector<physx::PxRigidStatic*> Physics3D::m_RigidStatic_arr;
	physx::PxCooking* Physics3D::m_cooking = nullptr;
	physx::PxPvd* Physics3D::gPvd = nullptr;
	bool Physics3D::SimulatePhysics = false;
	std::vector<PhysicsDebug> Physics3D::DebugPoints;

	Physics3D::Physics3D()
	{
		//cube = new LoadMesh("Assets/Meshes/Cube.fbx");
		//Initilize();
	}
	Physics3D::~Physics3D()
	{

		//CleanUpPhysics();
	}
	void Physics3D::Initilize()
	{
		SetUpPhysics();
	}

	void Physics3D::UpdateTransform(TransformComponent& transform_component, PhysicsComponent& physics_component)
	{
		if (!physics_component.m_DynamicActor)
			return;

		physics_component.m_DynamicActor->setAngularDamping(physics_component.m_AngularDamping);
		physics_component.m_DynamicActor->setLinearDamping(physics_component.m_LinearDamping);
		physics_component.m_DynamicActor->setMass(physics_component.m_mass);

		if (physics_component.isKinematic)
		{
			glm::mat4x4 trans = transform_component.GetTransform();
			physx::PxTransform kinematic_transform = physx::PxTransform(*(physx::PxMat44*)glm::value_ptr(trans));
			physics_component.m_DynamicActor->setKinematicTarget(kinematic_transform);
		}
		else {
			if (SimulatePhysics)//if simulate physics is on then update transform
			{
				physx::PxTransform pxtransform = physics_component.m_DynamicActor->getGlobalPose();
				transform_component.m_transform = glm::translate(glm::mat4(1.0f), { pxtransform.p.x, pxtransform.p.y, pxtransform.p.z })
					* glm::mat4(glm::quat(pxtransform.q.w, pxtransform.q.x, pxtransform.q.y, pxtransform.q.z));
				transform_component.m_transform = glm::scale(transform_component.m_transform, transform_component.Scale);
			}
			else //if the simulate physics is false then set the collider transform same as the mesh
			{
				transform_component.m_transform = glm::mat4(1.0f);
				glm::mat4x4 trans = transform_component.GetTransform();
				physx::PxTransform transform = physx::PxTransform(*(physx::PxMat44*)glm::value_ptr(trans));
				physics_component.m_DynamicActor->setGlobalPose(transform);
			}
		}
	}
	void Physics3D::AddBoxCollider(const glm::vec3& halfExtent, const glm::mat4& transform, bool isStatic, const float& StaticFriction, const float& DynamicFriction, const float& Restitution)
	{
		m_defaultMaterial = m_physics->createMaterial(StaticFriction, DynamicFriction, Restitution);

		if (isStatic == true)
		{
			m_groundActor = m_physics->createRigidStatic(physx::PxTransform(*(physx::PxMat44*)glm::value_ptr(transform)));
			physx::PxShape* groundShape = m_physics->createShape(physx::PxBoxGeometry(halfExtent.x, halfExtent.y, halfExtent.z), *m_defaultMaterial);
			m_groundActor->attachShape(*groundShape);
			m_scene->addActor(*m_groundActor);
			m_RigidStatic_arr.push_back(m_groundActor);
			groundShape->release();
		}
		else {
			physx::PxShape* shape = m_physics->createShape(physx::PxBoxGeometry(halfExtent.x, halfExtent.y, halfExtent.z), *m_defaultMaterial);
			physx::PxTransform localTm(*(physx::PxMat44*)glm::value_ptr(transform));

			m_boxActor = physx::PxCreateDynamic(*m_physics, localTm, *shape, 10.0);
			m_RigidDynamic_arr.push_back(m_boxActor);

			m_boxActor->attachShape(*shape);
			physx::PxRigidBodyExt::updateMassAndInertia(*m_boxActor, 10.0f);
			m_boxActor->setAngularDamping(0.5f);
			m_boxActor->setLinearDamping(0.0f);
			m_boxActor->setLinearVelocity({ 0.0f,200.0f,0.0f });
			m_scene->addActor(*m_boxActor);
			shape->release();
		}
	}
	void Physics3D::AddBoxCollider(PhysicsComponent& physics_component)
	{
		m_defaultMaterial = m_physics->createMaterial(physics_component.m_StaticFriction, physics_component.m_DynamicFriction, physics_component.m_Restitution);
		physx::PxShape* shape = m_physics->createShape(physx::PxBoxGeometry(physics_component.m_halfextent.x, physics_component.m_halfextent.y, physics_component.m_halfextent.z), *m_defaultMaterial);
		physx::PxTransform localTm(*(physx::PxMat44*)glm::value_ptr(physics_component.m_transform));

		if (physics_component.isStatic == true)
		{
			physics_component.m_StaticActor = physx::PxCreateStatic(*m_physics, localTm, *shape);
			m_scene->addActor(*physics_component.m_StaticActor);
			shape->release();
		}
		else {
			physics_component.m_DynamicActor = physx::PxCreateDynamic(*m_physics, localTm, *shape, physics_component.m_mass);
			if (physics_component.isKinematic)
				physics_component.m_DynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);
			else
				physics_component.m_DynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, false);

			physx::PxRigidBodyExt::updateMassAndInertia(*physics_component.m_DynamicActor, physics_component.m_mass);
			m_scene->addActor(*physics_component.m_DynamicActor);
			shape->release();
		}
	}
	void Physics3D::AddSphereCollider(PhysicsComponent& physics_component)
	{
		m_defaultMaterial = m_physics->createMaterial(physics_component.m_StaticFriction, physics_component.m_DynamicFriction, physics_component.m_Restitution);
		physx::PxShape* shape = m_physics->createShape(physx::PxSphereGeometry(physics_component.m_radius), *m_defaultMaterial);

		physx::PxTransform localTm(*(physx::PxMat44*)glm::value_ptr(physics_component.m_transform));
		if (physics_component.isStatic == false)
		{
			physics_component.m_DynamicActor = physx::PxCreateDynamic(*m_physics, localTm, *shape, physics_component.m_mass);

			if (physics_component.isKinematic)
				physics_component.m_DynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);
			else
				physics_component.m_DynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, false);

			//physics_component.m_DynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD, true);
			//physics_component.m_DynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eENABLE_CCD_FRICTION, true);

			physx::PxRigidBodyExt::updateMassAndInertia(*physics_component.m_DynamicActor, physics_component.m_mass);
			m_scene->addActor(*physics_component.m_DynamicActor);
			shape->release();
		}
		else
		{
			physics_component.m_StaticActor = physx::PxCreateStatic(*m_physics, localTm, *shape);
			m_scene->addActor(*physics_component.m_StaticActor);
			shape->release();
		}
	}
	void Physics3D::AddCapsuleCollider(PhysicsComponent& physics_component)
	{
	}
	void Physics3D::AddPlaneCollider(PhysicsComponent& physics_component)
	{
	}
	void Physics3D::AddMeshCollider(const std::vector<glm::vec3>& vertices, const std::vector<unsigned int>& indices, const glm::vec3& scaling, PhysicsComponent& physics_component)
	{
		m_defaultMaterial = m_physics->createMaterial(physics_component.m_StaticFriction, physics_component.m_DynamicFriction, physics_component.m_Restitution);
		physx::PxTransform localTm(*(physx::PxMat44*)glm::value_ptr(physics_component.m_transform));

		if (physics_component.isStatic) // for static rigid bodies, use triangle mesh for better accuracy
		{
			// Set up the triangle mesh descriptor
			physx::PxTriangleMeshDesc triMeshDesc;
			triMeshDesc.points.count = vertices.size();
			triMeshDesc.points.data = &vertices[0].x;
			triMeshDesc.points.stride = sizeof(glm::vec3);
			triMeshDesc.triangles.count = indices.size() / 3;  // Ensure the triangles are counted correctly
			triMeshDesc.triangles.data = &indices[0];
			triMeshDesc.triangles.stride = 3 * sizeof(unsigned int);

			physx::PxCookingParams cookingParams(m_physics->getTolerancesScale());

			physx::PxTriangleMesh* triMesh = PxCreateTriangleMesh(cookingParams, triMeshDesc);
			if (!triMesh)
			{
				CN_CORE_ERROR("Error creating triangle mesh");
				return;
			}

			// Set up the static mesh
			physx::PxShape* staticShape = m_physics->createShape(physx::PxTriangleMeshGeometry(triMesh, physx::PxMeshScale(*(physx::PxVec3*)glm::value_ptr(scaling))), *m_defaultMaterial);
			if (!staticShape)
			{
				CN_CORE_ERROR("Error creating static shape");
				return;
			}

			physics_component.m_StaticActor = physx::PxCreateStatic(*m_physics, localTm, *staticShape);
			if (!physics_component.m_StaticActor)
			{
				CN_CORE_ERROR("Error creating static actor");
				return;
			}

			m_scene->addActor(*physics_component.m_StaticActor);
			staticShape->release();
			triMesh->release();
		}
		else // for dynamic rigid bodies, use convex colliders
		{
			// Set up the convex mesh descriptor
			physx::PxConvexMeshDesc convexMeshDesc;
			convexMeshDesc.points.count = vertices.size();
			convexMeshDesc.points.data = &vertices[0];
			convexMeshDesc.points.stride = sizeof(glm::vec3);
			convexMeshDesc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX | physx::PxConvexFlag::eGPU_COMPATIBLE;

			physx::PxCookingParams cookingParams(m_physics->getTolerancesScale());
			// Create the convex mesh directly
			physx::PxConvexMesh* convexMesh = PxCreateConvexMesh(cookingParams, convexMeshDesc);
			if (!convexMesh)
			{
				CN_CORE_ERROR("Error creating convex mesh");
				return;
			}

			// Set up the shape
			physx::PxShape* shape = m_physics->createShape(physx::PxConvexMeshGeometry(convexMesh, physx::PxMeshScale(*(physx::PxVec3*)glm::value_ptr(scaling))), *m_defaultMaterial);
			if (!shape)
			{
				CN_CORE_ERROR("Error creating shape");
				return;
			}

			// Set up dynamic rigid body
			physics_component.m_DynamicActor = physx::PxCreateDynamic(*m_physics, localTm, *shape, physics_component.m_mass);
			if (!physics_component.m_DynamicActor)
			{
				CN_CORE_ERROR("Error creating dynamic actor");
				return;
			}

			if (physics_component.isKinematic)
			{
				physics_component.m_DynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, true);
			}
			else
			{
				physics_component.m_DynamicActor->setRigidBodyFlag(physx::PxRigidBodyFlag::eKINEMATIC, false);
			}

			physx::PxRigidBodyExt::updateMassAndInertia(*physics_component.m_DynamicActor, physics_component.m_mass);
			m_scene->addActor(*physics_component.m_DynamicActor);
			shape->release();
			convexMesh->release();
		}
	}

	void Physics3D::AddHeightFieldCollider(const std::vector<int>& HeightValues, int width, int height, float spacing, const glm::mat4& transform)
	{
		m_defaultMaterial = m_physics->createMaterial(0.6, 0.6, 0.7);

		physx::PxTransform localTm(*(physx::PxMat44*)glm::value_ptr(transform));
		physx::PxHeightFieldSample* samples = new physx::PxHeightFieldSample[HeightValues.size()];
		for (int i = 0; i < HeightValues.size(); i++)
		{
			samples[i].height = HeightValues[i];
			samples[i].materialIndex0 = 3;
			samples[i].materialIndex1 = 3;
		}

		physx::PxHeightFieldDesc hfDesc;
		hfDesc.format = physx::PxHeightFieldFormat::eS16_TM;
		hfDesc.nbColumns = width / spacing;
		hfDesc.nbRows = height / spacing;
		hfDesc.samples.data = samples;
		hfDesc.samples.stride = sizeof(physx::PxHeightFieldSample);
		hfDesc.flags = physx::PxHeightFieldFlag::eNO_BOUNDARY_EDGES;

		physx::PxHeightField* aHeightField = PxCreateHeightField(hfDesc, m_physics->getPhysicsInsertionCallback());
		// flags = physx::PxMeshGeometryFlags::PxFlags::;
		physx::PxHeightFieldGeometry hfGeom(aHeightField, physx::PxMeshGeometryFlags(), 1, spacing,
			spacing);
		//physx::PxRigidActorExt::createExclusiveShape()
		physx::PxShape* aHeightFieldShape = m_physics->createShape(hfGeom, *m_defaultMaterial);
		auto StaticHf = physx::PxCreateStatic(*m_physics, localTm, *aHeightFieldShape);
		StaticHf->setActorFlag(physx::PxActorFlag::eVISUALIZATION, true);
		m_scene->addActor(*StaticHf);
		aHeightFieldShape->release();

	}
	void Physics3D::DebugPhysicsColliders()
	{
		m_scene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0f);
		m_scene->setVisualizationParameter(physx::PxVisualizationParameter::eCOLLISION_SHAPES, 2.0f);
		const physx::PxRenderBuffer& rb = m_scene->getRenderBuffer();
		DebugPoints.resize(rb.getNbLines());

		for (int i = 0; i < rb.getNbLines(); i++)
		{
			const physx::PxDebugLine& line = rb.getLines()[i];
			DebugPoints[i].pos0 = *(glm::vec3*)&line.pos0;
			DebugPoints[i].pos1 = *(glm::vec3*)&line.pos1;
			DebugPoints[i].color = *(glm::vec3*)&line.color0;
		}
	}
	void Physics3D::AddForce(PhysicsComponent& physics_component)
	{
		if (physics_component.m_DynamicActor)
		{
			physics_component.m_DynamicActor->addForce(*(physx::PxVec3*)glm::value_ptr(physics_component.m_ForceDirection), physx::PxForceMode::eVELOCITY_CHANGE);
		}
	}
	void Physics3D::RemoveActor(PhysicsComponent& physics_component)
	{
		if (physics_component.m_DynamicActor) {
			m_scene->removeActor(*physics_component.m_DynamicActor);
			physics_component.m_DynamicActor->release();
			physics_component.m_DynamicActor = nullptr;
		}
		if (physics_component.m_StaticActor) {
			m_scene->removeActor(*physics_component.m_StaticActor);
			physics_component.m_StaticActor->release();
			physics_component.m_StaticActor = nullptr;
		}
	}
	bool Physics3D::Raycast(const glm::vec3& origin, const glm::vec3& dir, const float& dist, HitResult& Hit)
	{
		physx::PxRaycastBuffer hit;
		//ray casting using origin , ray direction and distance travelled by the ray
		bool isSuccess = m_scene->raycast(*(physx::PxVec3*)&origin, *(physx::PxVec3*)&dir, dist, hit);

		Hit.Distance = hit.block.distance;
		Hit.FaceIndex = hit.block.faceIndex;
		Hit.Normal = *(glm::vec3*)&hit.block.normal;
		Hit.Position = *(glm::vec3*)&hit.block.position;
		Hit.u = hit.block.u;
		Hit.v = hit.block.v;
		return isSuccess;
	}
	uint32_t Physics3D::GetNbActors()
	{
		return m_scene->getNbActors(physx::PxActorTypeFlag::eRIGID_DYNAMIC | physx::PxActorTypeFlag::eRIGID_STATIC);
	}
	void Physics3D::CleanUpPhysics()
	{
		m_boxActor->release();
		m_groundActor->release();
		m_dispatcher->release();
		m_scene->release();
		m_physics->release();
		m_foundation->release();
		m_scene = nullptr;
		m_dispatcher = nullptr;
		m_physics = nullptr;
		m_foundation = nullptr;
		m_boxActor = nullptr;
		m_groundActor = nullptr;
	}
	physx::PxU32 x;
	void Physics3D::StepPhysics()
	{
		float ts = 1.0f / 240.0f;
		m_scene->simulate(ts);
		m_scene->fetchResults(true);
		//std::cout << "Simulating" <<x<< std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(int(ts * 1000)));

		DebugPhysicsColliders();
	}
	void Physics3D::SetUpPhysics()
	{
		// Set up the foundation, allocator, and error callback
		physx::PxDefaultAllocator mDefaultAllocatorCallback;
		physx::PxDefaultErrorCallback mDefaultErrorCallback;
		m_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, mDefaultAllocatorCallback, mDefaultErrorCallback);

		// Create CUDA context manager for GPU acceleration (if needed)
		physx::PxCudaContextManagerDesc cudaContextManagerDesc;
		gCudaContextManager = PxCreateCudaContextManager(*m_foundation, cudaContextManagerDesc);
		if (!gCudaContextManager)
		{
			CN_CORE_ERROR("Error in creating CUDA context manager");
			return;
		}

		// In PhysX 5.x, cooking is integrated with the PxPhysics object, no need for PxCreateCooking
		physx::PxTolerancesScale toleranceScale;
		m_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_foundation, toleranceScale);
		if (!m_physics)
		{
			CN_CORE_ERROR("Error in creating physics object");
			return;
		}

		// No need for PxRegisterHeightFields in PhysX 5.x
		// Cooking is now integrated with PxPhysics, so heightfields will be handled through the new API

		// Create the CPU dispatcher and configure the scene
		physx::PxSceneDesc sceneDesc(m_physics->getTolerancesScale());
		sceneDesc.gravity = physx::PxVec3(0.0f, -981.f, 0.0f);
		m_dispatcher = physx::PxDefaultCpuDispatcherCreate(4);
		if (!m_dispatcher)
		{
			CN_CORE_ERROR("Error creating CPU dispatcher");
			return;
		}

		sceneDesc.cpuDispatcher = m_dispatcher;
		sceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
		sceneDesc.cudaContextManager = gCudaContextManager;
		sceneDesc.flags |= physx::PxSceneFlag::eENABLE_GPU_DYNAMICS;
		sceneDesc.broadPhaseType = physx::PxBroadPhaseType::eGPU;

		m_scene = m_physics->createScene(sceneDesc);
		if (!m_scene)
		{
			CN_CORE_ERROR("Error creating physics scene");
			return;
		}

		// Now the physics scene is ready to be simulated in the main loop
	}
}