//================================================================================
//TOON LINES VERTEX SHADER
//================================================================================

varying float alpha;
varying vec3 VertexNormal;

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    VertexNormal = gl_NormalMatrix * gl_Normal;
    alpha = gl_Position.z*100 ;
}
