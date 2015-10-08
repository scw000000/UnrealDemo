// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "DemoEnums.h"
#include "BasicCharacter.generated.h"

class UPawnNoiseEmitterComponent;
UCLASS()
class DEMO_API ABasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
   ABasicCharacter( const FObjectInitializer& ObjectInitializer );

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

   virtual void Jump( ) override;

   virtual void ToggleProne();
   	
   virtual void StartAttack();

   virtual void StopAttack();

   virtual void CatchAnimNotifies();

	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

   virtual void Crouch( bool bClientSimulation = false ) override;

   virtual void UnCrouch( bool bClientSimulation = false ) override;

   void SetPlayerView( PlayerViews inViewType );
   
   //custom function for movement
   virtual void MoveForward( float amount );

   //custom function for movement
   virtual void MoveRight( float amount );

   void SetCamYaw( const float& amount );

   void SetCamPitch( const float& amount );

   void SetCamDistance( const float& amount );

   void SetTeamNumber( int32 newTeamNumber );

   /** Take damage, handle death */
	virtual float TakeDamage( float damage, FDamageEvent const& damageEvent, AController* eventInstigator, AActor* damageCauser ) override;

   int32 GetTeamNumber() const;

   bool IsAlive() const;

   bool IsEnemyFor( AController* testController );

   bool IsEnemyFor( ABasicCharacter * testCharacter );

   bool CanDie( float killingDamage, FDamageEvent const& damageEvent, AController* killer, AActor* damageCauser ) const;

   bool Die( float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser );

   

   UFUNCTION( BlueprintCallable, Category = LineTrace )
      FHitResult PerfromVisionLineTrace();

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      float maxCameraPitch;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      float minCameraPitch;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      float cameraScrollSpeed;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      float cameraRotateSpeed;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      float maxCameraDistance;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      float minCameraDistance;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = PlayerMotion )
      float idleTime;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerHealth )
      float health;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerHealth )
      float maxHealth;

   UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = PlayerTeam )
      int32 teamNumber;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      USpringArmComponent* thirdPersonCameraBoomYaw;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      USpringArmComponent* thirdPersonCameraBoomPitch;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      UCameraComponent* playerCamera;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      USpringArmComponent* aimingCameraBoom;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerView )
      PlayerViews playerView;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerMotion )
      ArmMotions armMotion;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = PlayerMotion )
      BodyMotions bodyMotion;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = CameraShake)
	  TSubclassOf<UCameraShake> damagedCameraShake;

   UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = Noise )
     UPawnNoiseEmitterComponent* noiseEmitterComp;

protected:
  void WakePlayer();

  void AddIdleTime( const float& inTime );

  void RefineMotionType( const float& DeltaSeconds );

  void RefineMotionStand( const float& DeltaSeconds );

  void RefineMotionJog( );

  void RefineMotionCrouch( );

  void RefineMotionFall();

  void RefineMotionJump( );

  void RefineMotionJogJump( );

  void RefineMotionBreak( );

  void OnDeath( float killingDamage, struct FDamageEvent const& damageEvent, class APawn* pawnInstigator, class AActor* damageCauser );

  void PlayHitReaction( float damageTaken, struct FDamageEvent const& damageEvent, class APawn* pawnInstigator, class AActor* damageCauser );

  bool isDying;

private:
   void SetPlayerViewToThirdPerson( );

   void SetPlayerViewToAim( );

   void SetPlayerViewToFirstPerson( );

   void UpdateCameraLocationAndRotation( const float& DeltaSeconds );
};
