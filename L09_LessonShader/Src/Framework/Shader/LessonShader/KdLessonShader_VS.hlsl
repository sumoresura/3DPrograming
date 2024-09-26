#include "../inc_KdCommon.hlsli"
#include "inc_KdLessonShader.hlsli"

VSOutput main( float4 pos : POSITION ) : SV_POSITION
{
	VSOutput Out;

	//受け取った位置をそのまま渡す
	Out.Pos = pos;

	//ここ重要！(座標変換)
	Out.Pos = mul(pos,     g_mWorld);
	Out.Pos = mul(Out.Pos, g_mView);
	Out.Pos = mul(Out.Pos, g_mProj);

	return Out;
}
