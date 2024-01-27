#pragma once
#include <Siv3D.hpp>

class StageList
{

private:

	String Num;//ステージナンバー
	String Name;//ステージ名
	String Comment;//コメント，説明，概要
	FilePath Stagepath;//CSVファイルパス

public:

	StageList(String SetNum, String SetName, String SetComment, FilePath Setpath)
	{
		Num = SetNum;
		Name = SetName;
		Comment = SetComment;
		Stagepath = Setpath;
	}

	//ステージナンバーの閲覧
	String readNum() const
	{
		return Num;
	}

	//ステージ名の閲覧
	String readName() const
	{
		return Name;
	}

	//ステージ概要の閲覧
	String readComment() const
	{
		return Comment;
	}

	//ファイルパスの閲覧
	FilePath readStagepath() const
	{
		return Stagepath;
	}
};
