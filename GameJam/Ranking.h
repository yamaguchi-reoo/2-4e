#pragma once

#define RANK 5

struct RankingData
{
	int no;
	int score;
};

class RANKING
{
private:
	static RankingData data[RANK];
private:
	//コンストラクタ
	RANKING() = default;

	//ランキングの並べ替え
	static void SortRanking();

	//ランキングデータの保存
	static void SaveRanking();
public:

	//ランキングデータの更新
	static void Insert(int score);

	//ランキングデータ読み込み
	static void ReadRanking();

	//ランキングの取得の取得
	static RankingData GetData(int n){ return data[n]; }
};

