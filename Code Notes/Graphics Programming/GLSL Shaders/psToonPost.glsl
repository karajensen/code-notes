//================================================================================
//TOON COMPOSITING PIXEL SHADER
//================================================================================

uniform sampler2D TexSampler;
uniform sampler2D NormalSampler;
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
    //look up original color
    vec4 scene = texture2D(TexSampler, UV);

    //look up values from normal texture, offset along four diagonals from pixel looking at
    vec2 edgeOffset = EdgeWidth / ScreenResolution;

    vec4 n1 = texture2D(NormalSampler, UV + vec2(-1, -1) * edgeOffset);
    vec4 n2 = texture2D(NormalSampler, UV + vec2( 1,  1) * edgeOffset);
    vec4 n3 = texture2D(NormalSampler, UV + vec2(-1,  1) * edgeOffset);
    vec4 n4 = texture2D(NormalSampler, UV + vec2( 1, -1) * edgeOffset);

    //Work out how much the normal and depth values are changing.
    vec4 diagonalDelta = abs(n1 - n2) + abs(n3 - n4);

    float normalDelta = dot(diagonalDelta.xyz, vec3(1.0,1.0,1.0));
    float depthDelta = diagonalDelta.w;
        
    //Filter out very small changes, in order to produce nice clean results.
    normalDelta = clamp((normalDelta - NormalThreshold) * NormalSensitivity, 0.0, 1.0);
    depthDelta = clamp((depthDelta - DepthThreshold) * DepthSensitivity, 0.0, 1.0);

    //Does this pixel lie on an edge?
    float edgeAmount = clamp(normalDelta + depthDelta, 0.0, 1.0) * EdgeIntensity;

    //Apply the edge detection result to the main scene color.
    scene *= (1 - edgeAmount);


    gl_FragColor = scene;
}
