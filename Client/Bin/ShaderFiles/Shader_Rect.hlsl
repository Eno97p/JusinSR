/* VertexShader, PixelShader */

// D3DDECLUSAGE

// float2x2, float3x3, float1x3, float4x4 == matrix
/* ���̴��� �������� == ������̺� */
matrix g_WorldMatrix, g_ViewMatrix, g_ProjMatrix;
float g_fData = 0.0f;
texture g_Texture;
texture g_Texture1;

/* �� �ؽ��ĸ��� ���� ��� ���;��ϴ����� ���ؼ� ������ ������Ѵ�. */
sampler DefaultSampler = sampler_state
{
    texture = g_Texture;
    minfilter = linear;
    magfilter = linear;
    mipfilter = linear;
};

sampler DefaultSampler1 = sampler_state
{
    texture = g_Texture1;
    minfilter = linear;
    magfilter = linear;
    mipfilter = linear;
};



struct VS_IN
{
    float3 vPosition : POSITION;
    float2 vTexcoord : TEXCOORD0;
};

struct VS_OUT
{
    float4 vPosition : POSITION;
    float2 vTexcoord : TEXCOORD0;
    float4 vWorldPos : TEXCOORD1;
};

/* �������̴� : ������ ��ȯ(����, ��, ����) + ������ ���������� �����Ѵ�. */
VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out = (VS_OUT) 0;

    vector vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
    Out.vWorldPos = vPosition;

    vPosition = mul(vPosition, g_ViewMatrix);
    vPosition = mul(vPosition, g_ProjMatrix);

    Out.vPosition = vPosition;
    Out.vTexcoord = In.vTexcoord;

    return Out;
}

/* /W ������ �����Ѵ�. (����) */
/* ����Ʈ ��ȯ (�����T��ǥ��) */
/* ����Ż���̤Ѥ� -> ���������� ��������Ͽ� �ѷ��׿��� �ȼ��� �������. */

struct PS_IN
{
    float4 vPosition : POSITION;
    float2 vTexcoord : TEXCOORD0;
    float4 vWorldPos : TEXCOORD1;
};

struct PS_OUT
{
    vector vColor : COLOR0;
};



/* �ȼ����̴� : �ȼ��� ���� �����ϳ�. */
vector PS_MAIN(PS_IN In) : COLOR0
{
    vector vColor = (vector) 0;

	
    vColor = tex2D(DefaultSampler, In.vTexcoord);

    In.vWorldPos.y;

    vColor = vector(vColor.r, vColor.g , vColor.b , vColor.a - 0.1f);



	// vColor = vector(1.0f, 0.f, 0.f, In.vTexcoord.y);

    return vColor;
}



/* �׷��� ī�忡�� �����ϴ� ���̴� ������ ���� �ٸ� ������� ���̴��� �����Ѵ�. */
technique DefaultTechnique
{
	/* Pass : ���̴� ����� ĸ��ȭ. */
	/* ��� + ��ָ��� + ������Ʈ + PBR + SSAO */
    pass DefaultPass
    {
		// fillmode = wireframe;
        //AlphaBlendEnable = true;
        //SrcBlend = SrcAlpha;
        //DestBlend = InvSrcAlpha;
        //bLENDoP = aDD;

		/* ������ �ۼ��� ���� ���̴��� ������ �����ϰ� ������ �Լ��� �����Ѵ�. */
        VertexShader = compile vs_3_0 VS_MAIN();
		/* ������ �ۼ��� �ȼ� ���̴��� ������ �����ϰ� ������ �Լ��� �����Ѵ�. */
        PixelShader = compile ps_3_0 PS_MAIN();
    }

	/* ������Ʈ + ����� + ���ĺ��� */
	//pass DefaultPass2
	//{
	//	/* ������ �ۼ��� ���� ���̴��� ������ �����ϰ� ������ �Լ��� �����Ѵ�. */
	//	VertexShader = compile vs_3_0 VS_MAIN();
	//	/* ������ �ۼ��� �ȼ� ���̴��� ������ �����ϰ� ������ �Լ��� �����Ѵ�. */
	//	PixelShader = compile ps_3_0 PS_MAIN();
	//}

}

