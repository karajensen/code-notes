//================================================================================
//TOON COMPOSITING PIXEL SHADER
//================================================================================

varying float EdgeWidth;
varying float EdgeIntensity;
varying float NormalThreshold;
varying float DepthThreshold;
varying float NormalSensitivity;
varying float DepthSensitivity;
varying vec2 ScreenResolution;
varying vec2 UV;

void main()
{
    //TRANSFORM VERTEX
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

    //PASS UVS
    UV = gl_MultiTexCoord0.xy;

    EdgeWidth = 1.2;
    EdgeIntensity = 1.0;

    NormalThreshold = 0.05;
    NormalSensitivity = 0.5;

    DepthThreshold = 0.1;
    DepthSensitivity = 10.0;

    //ScreenResolution.x = 1024.0;
    //ScreenResolution.y = 1024.0;
    
    ScreenResolution.y = 1500.0;
    ScreenResolution.x = 1500.0;

}
