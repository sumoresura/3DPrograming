﻿#pragma once

class KdLessonShader
{
public:

	// 定数バッファ(オブジェクト単位更新)
	struct cbObject
	{
		// UV操作
		Math::Vector2	UVOffset = { 0.0f, 0.0f };
		Math::Vector2	UVTiling = { 1.0f, 1.0f };

		int				EnableOutLineDraw = 0;
		float			_blank[3] = {0,0,0};
	};

	// 定数バッファ(メッシュ単位更新)
	struct cbMesh
	{
		Math::Matrix mW;
	};

	// 定数バッファ(マテリアル単位更新)
	struct cbMaterial
	{
		Math::Vector4	BaseColor	= {1.0f, 1.0f, 1.0f, 1.0f};

		Math::Vector3	Emissive	= { 1.0f, 1.0f, 1.0f };
		float			Metallic	= 0.0f;
		
		float			Roughness	= 1.0f;
		float			_blank[3]	= {0.0f, 0.0f, 0.0f };
	};
public:

    //================================================
    // 初期化・解放
    //================================================

    // 初期化
    bool Init();
    // 解放
    void Release();

    // デストラクタで自動で解放するようにする
    ~KdLessonShader() { Release(); }

	//アウトライン描画設定
	void SetEnableOutLineDraw(const bool enableOutLineDraw)
	{
		if (m_cb0_Obj.Work().EnableOutLineDraw != static_cast<int>(enableOutLineDraw))
		{
			m_cb0_Obj.Work().EnableOutLineDraw = enableOutLineDraw;
			m_dirtyCBObj = true;
		}
	}

	// UVオフセット設定
	void SetUVOffset(const Math::Vector2 & offset)
	{
		m_cb0_Obj.Work().UVOffset = offset;
		m_dirtyCBObj = true;
	}

	// IBLテクスチャの設定
	void SetIBLTexture(KdTexture& iblTex)
	{
		KdDirect3D::Instance().WorkDevContext()->
			PSSetShaderResources(12, 1, iblTex.WorkSRViewAddress());
	}

	//================================================
	// 各定数バッファの取得
	//================================================
	const cbObject& GetObjectCB() const { return m_cb0_Obj.Get(); }

    //================================================
    // 描画準備
    //================================================
    // 陰影をつけるオブジェクト等を描画する前後に行う
    void Begin();
    void End();

    //================================================
    // 描画関数
    //================================================
    // メッシュ描画
    void DrawMesh(const KdMesh* mesh, const Math::Matrix& mWorld, const std::vector<KdMaterial>& materials,
        const Math::Vector4& col, const Math::Vector3& emissive);

    // モデルデータ描画：アニメーションに非対応
    void DrawModel(const KdModelData& rModel, const Math::Matrix& mWorld = Math::Matrix::Identity,
        const Math::Color& colRate = kWhiteColor, const Math::Vector3& emissive = Math::Vector3::Zero);

	// モデルワーク描画：アニメーションに対応
	void DrawModel(KdModelWork& rModel, const Math::Matrix& mWorld = Math::Matrix::Identity,
		const Math::Color& colRate = kWhiteColor, const Math::Vector3& emissive = Math::Vector3::Zero);

private:
	//アウトライン描画設定フラグの取得
	bool GetEnableOutLineDraw() { return m_cb0_Obj.Work().EnableOutLineDraw; }

	//定数バッファを初期状態に戻す
	void ResetCBObject();

	// マテリアルのセット
	void WriteMaterial(	const KdMaterial& material, const Math::Vector4& colRate,
						const Math::Vector3& emiRate);

    ID3D11VertexShader* m_VS            = nullptr;  // 頂点シェーダー
    ID3D11PixelShader*  m_PS            = nullptr;  // ピクセルシェーダー

    ID3D11InputLayout*  m_inputLayout   = nullptr;  // 頂点入力レイアウト

	// 定数バッファ
	KdConstantBuffer<cbObject>		m_cb0_Obj;		// オブジェクト単位で更新
	KdConstantBuffer<cbMesh>		m_cb1_Mesh;		// メッシュ毎に更新
	KdConstantBuffer<cbMaterial>	m_cb2_Material;	// マテリアル毎に更新

	bool m_dirtyCBObj = false;	//定数バッファのオブジェクトに変更があったかどうか

};
