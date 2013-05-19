//=========================================================================
//NO LIGHTING, SHADOW PROJECTION VERTEX SHADER
//=========================================================================
uniform vec4 LightColor;
uniform vec3 pPlane;
uniform vec3 nPlane;

void main()
{
    float depth = gl_Vertex.w;
    vec3 temp = vec3(gl_Vertex.x,gl_Vertex.y,gl_Vertex.z);

    float distance = dot((temp - pPlane), nPlane); 
    if(distance < 0)
        distance *= -1;
    
    vec3 pointToPlane = -(distance*nPlane);    
    
    vec4 pos;
    pos = gl_Vertex + vec4(pointToPlane.x,pointToPlane.y,pointToPlane.z,0);
    pos.w = depth;

    gl_Position = gl_ModelViewProjectionMatrix * pos;
}
