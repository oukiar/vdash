
//--------------------------------------------------------------------------------------
// Vertex shader
// We use the register semantic here to directly define the input register
// matWVP.  Conversely, we could let the HLSL compiler decide and check the
// constant table.
//--------------------------------------------------------------------------------------
static const char *         g_strVertexShaderProgram =
    " float4x4 matWVP : register(c0);              "
    "                                              "
    " struct VS_IN                                 "
    "                                              "
    " {                                            "
    "     float4 ObjPos   : POSITION;              "  // Object space position 
    "     float2 UV    : TEXCOORD0;                 "  // Vertex color                 
    " };                                           "
    "                                              "
    " struct VS_OUT                                "
    " {                                            "
    "     float4 ProjPos  : POSITION;              "  // Projected space position 
    "     float2 UV    : TEXCOORD0;                 "
    " };                                           "
    "                                              "
    " VS_OUT main( VS_IN In )                      "
    " {                                            "
    "     VS_OUT Out;                              "
    "     Out.ProjPos = mul( matWVP, In.ObjPos );  "  // Transform vertex into
	"     Out.UV = In.UV;							"  // UV
    "     return Out;                              " 
    " }                                            ";


//--------------------------------------------------------------------------------------
// Pixel shader
//--------------------------------------------------------------------------------------
static const char *         g_strPixelShaderProgram =
	" sampler s : register(s0) ;				   "
    " struct PS_IN                                 "
    " {                                            "
    "     float2 UV : TEXCOORD0;                  "  // Interpolated color from                      
    " };                                           "  // the vertex shader
    "                                              "
    " float4 main( PS_IN In ) : COLOR              "
    " {                                            "
    "     return tex2D(s,In.UV);                         "  // Output color
    " }                                            ";

//--------------------------------------------------------------------------------------
// Reflexion Pixel shader
//--------------------------------------------------------------------------------------
static const char *         g_strPixelRShaderProgram =
	" sampler s : register(s0) ;				   "
    " struct PS_IN                                 "
    " {                                            "
    "     float2 UV : TEXCOORD0;                  "  // Interpolated color from                      
    " };                                           "  // the vertex shader
    "                                              "
    " float4 main( PS_IN In ) : COLOR              "
    " {                                            "
	"   In.UV.y = 1-In.UV.y;"
	"	float4 color = tex2D(s,In.UV);				"
	"	color.a= In.UV.y*0.6;			"
    "     return color;                         "  // Output color
    " }       ";