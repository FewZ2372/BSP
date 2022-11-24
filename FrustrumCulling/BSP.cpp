#include "raylib.h"
#include "raymath.h"

struct Frustrum
{
	Vector2 direction;
	Vector2 pos;
	int sides;
	float radius;
	float rotation;
	float lineThickness;
	float speed;
	float maxSpeed;
};

Frustrum frustrum;

struct Rectangles
{
	Rectangle rec;

};

Rectangles rectangle[9];

void DrawMap();
void setRectangles();
void DrawFrustrum();
void setFrustrum();
void Update();
void frustrumMovement();
void accelerateFrustrum(float axisX, float axisY, Frustrum& frustrum);
float getRotation(Vector2 dir);
float getVectorMagnitude(Vector2 vec);
Vector2 normalizeVector(Vector2 vec);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 900;
	const int screenHeight = 900;

	InitWindow(screenWidth, screenHeight, "Frustrum");

	setFrustrum();
	setRectangles();
	SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())        // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		Update();
		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawMap();
		DrawFrustrum();

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}

void Update()
{

	frustrumMovement();
}

void DrawFrustrum()
{
	Vector2 rotation = { GetMouseX() - frustrum.pos.x, GetMouseY() - frustrum.pos.y };
	DrawPolyLinesEx(frustrum.pos, frustrum.sides, frustrum.radius, getRotation(rotation), frustrum.lineThickness, BLACK);
}

void DrawMap()
{
	DrawRectangleRec(rectangle[0].rec, RED);
	DrawRectangleRec(rectangle[1].rec, BLUE);
	DrawRectangleRec(rectangle[2].rec, GREEN);
	DrawRectangleRec(rectangle[3].rec, YELLOW);
	DrawRectangleRec(rectangle[4].rec, LIME);
	DrawRectangleRec(rectangle[5].rec, SKYBLUE);
	DrawRectangleRec(rectangle[6].rec, PINK);
	DrawRectangleRec(rectangle[7].rec, PURPLE);
	DrawRectangleRec(rectangle[8].rec, MAROON);
	DrawRectangleRec(rectangle[9].rec, GRAY);

}

void setRectangles()
{
	rectangle[0].rec.x = 0;
	rectangle[0].rec.y = 0;
	rectangle[0].rec.width = 300;
	rectangle[0].rec.height = 300;

	rectangle[1].rec.x = rectangle[0].rec.width;
	rectangle[1].rec.y = 0;
	rectangle[1].rec.width = 300;
	rectangle[1].rec.height = 300;

	rectangle[2].rec.x = rectangle[0].rec.width + rectangle[1].rec.width;
	rectangle[2].rec.y = 0;
	rectangle[2].rec.width = 300;
	rectangle[2].rec.height = 300;




	rectangle[3].rec.x = 0;
	rectangle[3].rec.y = rectangle[0].rec.height;
	rectangle[3].rec.width = 300;
	rectangle[3].rec.height = 300;

	rectangle[4].rec.x = rectangle[3].rec.width;
	rectangle[4].rec.y = rectangle[1].rec.height;
	rectangle[4].rec.width = 300;
	rectangle[4].rec.height = 300;

	rectangle[5].rec.x = rectangle[3].rec.width + rectangle[4].rec.width;
	rectangle[5].rec.y = rectangle[2].rec.height;
	rectangle[5].rec.width = 300;
	rectangle[5].rec.height = 300;



	rectangle[6].rec.x = 0;
	rectangle[6].rec.y = rectangle[0].rec.height + rectangle[3].rec.height;
	rectangle[6].rec.width = 300;
	rectangle[6].rec.height = 300;

	rectangle[7].rec.x = rectangle[6].rec.width;
	rectangle[7].rec.y = rectangle[1].rec.height + rectangle[4].rec.height;
	rectangle[7].rec.width = 300;
	rectangle[7].rec.height = 300;

	rectangle[8].rec.x = rectangle[6].rec.width + rectangle[7].rec.width;
	rectangle[8].rec.y = rectangle[2].rec.height + rectangle[4].rec.height;
	rectangle[8].rec.width = 300;
	rectangle[8].rec.height = 300;
}

void setFrustrum()
{
	frustrum.pos.x = GetScreenWidth() / 2;
	frustrum.pos.y = GetScreenHeight() / 2;
	frustrum.sides = 3;
	frustrum.radius = 450;
	frustrum.rotation = 0;
	frustrum.lineThickness = 10;
	frustrum.direction.x = 0;
	frustrum.direction.y = 0;
	frustrum.speed = 10;
	frustrum.maxSpeed = 300;

}

void frustrumMovement()
{
	float axisX = 0;
	float axisY = 0;

	if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
	{
		Vector2 moveDir = { (float)GetMouseX(), (float)GetMouseY() };

		moveDir = normalizeVector({ moveDir.x - frustrum.pos.x, moveDir.y - frustrum.pos.y });

		axisX = moveDir.x;
		axisY = moveDir.y;

	}

	accelerateFrustrum(axisX, axisY, frustrum);
}

void accelerateFrustrum(float axisX, float axisY, Frustrum& frustrum)
{
	Vector2 newVel = frustrum.direction;

	newVel.x += axisX * frustrum.speed * GetFrameTime();
	newVel.y += axisY * frustrum.speed * GetFrameTime();

	if (newVel.x <= frustrum.maxSpeed)
	{
		frustrum.direction.x = newVel.x;
	}
	if (newVel.y <= frustrum.maxSpeed)
	{
		frustrum.direction.y = newVel.y;
	}

}

float getRotation(Vector2 dir)
{
	float rot = atan(dir.y / dir.x);

	rot = rot * 180 / PI;

	if (dir.x < 0)
	{
		rot += 180;
	}

	rot += 90;

	return rot;
}

float getVectorMagnitude(Vector2 vec)
{
	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
}

Vector2 normalizeVector(Vector2 vec)
{
	float mag = getVectorMagnitude(vec);

	return { vec.x / mag, vec.y / mag };
}