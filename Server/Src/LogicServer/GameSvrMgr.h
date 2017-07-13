#ifndef __GAME_SVR_MGR__
#define __GAME_SVR_MGR__

struct GameSvrInfo
{
	GameSvrInfo(UINT32 svrID, UINT32 conID)
	{
		dwSvrID = svrID;
		dwConnID = conID;
	}
	UINT32 dwSvrID;
	UINT32 dwConnID;
	UINT32 dwLoad;		//负载值
};

class CGameSvrMgr
{
private:
	CGameSvrMgr(void);
	~CGameSvrMgr(void);
public:
	static CGameSvrMgr* GetInstancePtr();
public:

	BOOL	DispatchPacket( NetPacket *pNetPacket);

	UINT32	GetServerIDByCopyID(UINT32 dwCopyID);

	UINT32	GetFreeGameServerID();

	BOOL	SendCreateSceneCmd(UINT32 dwServerID, UINT32 dwCopyType, UINT64 CreateParam);

	UINT32  GetConnIDBySvrID(UINT32 dwServerID);

	BOOL	GetMainScene(UINT32 &dwServerID, UINT32 &dwConnID, UINT32 &dwCopyID);
    BOOL    SendPlayerToCopy(UINT64 u64RoleID, UINT32 dwCopyType, UINT32 dwCopyID, UINT32 dwSvrID);
    BOOL	CreateScene(UINT32 dwCopyType, UINT64 CreateParam);
public:
	BOOL	OnCloseConnect(UINT32 dwConnID);
	BOOL	OnMsgGameSvrRegister(NetPacket *pNetPacket); //响应副本服务器注册
	BOOL	OnMsgCreateSceneAck(NetPacket *pNetPacket);  //响应创建副本成功
    BOOL    OnMsgTransRoleDataAck(NetPacket *pNetPacket);//响应角色数据传输成功
    BOOL    OnMsgEnterSceneReq(NetPacket *pNetPacket);
	//BOOL	OnMsgCopyReportReq(NetPacket *pNetPacket);
	
	

public:
	std::map<UINT32, GameSvrInfo> m_mapGameSvr; //服务器ID-->副本服务器信息
};

#endif
