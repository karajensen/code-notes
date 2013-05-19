//////////////////////////////////////////////////////////////////////////////
//OPENGL
//////////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------
OPENGL: Column Major Matrix / Right Handed Coordinate System
------------------------------------------------------------------
Trans * Rot * Scale = LocalWorld
ParentWorld * LocalWorld = World
Proj * Veiw * World * Vertex = FinalVertex in screenspace

| Right.x  Up.x  For.x  Pos.x |    UP: +Y
| Right.y  Up.y  For.y  Pos.y |    RIGHT: +X
| Right.z  Up.z  For.z  Pos.z |    FORWARD: -Z
|   0       0       0     1   |
------------------------------------------------------------------*/
