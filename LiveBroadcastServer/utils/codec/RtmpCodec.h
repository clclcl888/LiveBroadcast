#ifndef UTILS_CODEC_RTMPCODEC_H
#define UTILS_CODEC_RTMPCODEC_H

#include <cstdint>
#include <cstring>
#include <string>

#include "utils/Buffer.h"

/* 初期仅需要音视频数据 这里进行过滤*/
constexpr int MOVIE_CSID = 4;

/* 一下所有数据 用于握手部分和商定部分 采用的bilibili的握手商定抓包*/


constexpr uint8_t RTMP_SERVER_S01[1537] = { 0x03 };

constexpr uint8_t RTMP_SERVER_S2[1536] = {};

// Window Acknowledgement Size 5000000
constexpr uint8_t RTMP_SERVER_ACKNOWLEDGE_SIZE[] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x4b, 0x40 };

// Set Peer Bandwidth 5000000, Dynamic
constexpr uint8_t RTMP_SERVER_PEER_BANDWIDTH[] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x4b, 0x40, 0x02 };

// Set Chunk Size 4096
constexpr uint8_t RTMP_SERVER_SET_CHUNK_SIZE[] = { 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00 };

// _result('NetConnection.Connect.Success'
constexpr uint8_t RTMP_SERVER_CONNECT_RESULT[] = { 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0xbe, 0x14, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x07, 0x5f, 0x72,
	0x65, 0x73, 0x75, 0x6c, 0x74, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x06, 0x66, 0x6d, 0x73, 0x56, 0x65,
	0x72, 0x02, 0x00, 0x0d, 0x46, 0x4d, 0x53, 0x2f, 0x33, 0x2c, 0x30, 0x2c, 0x31, 0x2c, 0x31, 0x32, 0x33, 0x00, 0x0c, 0x63, 0x61, 0x70,
	0x61, 0x62, 0x69, 0x6c, 0x69, 0x74, 0x69, 0x65, 0x73, 0x00, 0x40, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09, 0x03,
	0x00, 0x05, 0x6c, 0x65, 0x76, 0x65, 0x6c, 0x02, 0x00, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x04, 0x63, 0x6f, 0x64, 0x65,
	0x02, 0x00, 0x1d, 0x4e, 0x65, 0x74, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x2e, 0x43, 0x6f, 0x6e, 0x6e, 0x65,
	0x63, 0x74, 0x2e, 0x53, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73, 0x00, 0x0b, 0x64, 0x65, 0x73, 0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f,
	0x6e, 0x02, 0x00, 0x15, 0x43, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x20, 0x73, 0x75, 0x63, 0x63, 0x65, 0x65, 0x64,
	0x65, 0x64, 0x2e, 0x00, 0x0e, 0x6f, 0x62, 0x6a, 0x65, 0x63, 0x74, 0x45, 0x6e, 0x63, 0x6f, 0x64, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09 };

// _result()
constexpr uint8_t RTMP_SERVER_RESULT[] = { 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x14, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x07, 0x5f, 0x72, 0x65,
	0x73, 0x75, 0x6c, 0x74, 0x00, 0x40, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// onStatus('NetStream.Publish.Start')
constexpr uint8_t RTMP_SERVER_START[] = { 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x69, 0x14, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x08, 0x6f, 0x6e, 0x53,
	0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x03, 0x00, 0x05, 0x6c, 0x65, 0x76, 0x65, 0x6c,
	0x02, 0x00, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x00, 0x04, 0x63, 0x6f, 0x64, 0x65, 0x02, 0x00, 0x17, 0x4e, 0x65, 0x74, 0x53, 0x74,
	0x72, 0x65, 0x61, 0x6d, 0x2e, 0x50, 0x75, 0x62, 0x6c, 0x69, 0x73, 0x68, 0x2e, 0x53, 0x74, 0x61, 0x72, 0x74, 0x00, 0x0b, 0x64, 0x65, 0x73,
	0x63, 0x72, 0x69, 0x70, 0x74, 0x69, 0x6f, 0x6e, 0x02, 0x00, 0x10, 0x53, 0x74, 0x61, 0x72, 0x74, 0x20, 0x70, 0x75, 0x62, 0x6c, 0x69, 0x73,
	0x68, 0x69, 0x6e, 0x67, 0x00, 0x00, 0x09 };

class FlvTag;
class RtmpPack
{
public:
	enum RtmpPackFmt : uint8_t
	{
		FMT0 = 0,
		FMT1 = 1,
		FMT2 = 2,
		FMT3 = 3
	};

	enum RtmpPackType : uint8_t
	{
		RTMP_OTHER = 0,
		RTMP_ABORT = 2,
		RTMP_ACKNOWLEDGE = 3,
		RTMP_CONTROL = 4,
		RTMP_AUDIO = 8,
		RTMP_VIDEO = 9,
		RTMP_SCRIPT = 18
	};

	RtmpPack() = default;
	~RtmpPack() = default;

	ssize_t DecodeHeader(const char* data, size_t length);

	RtmpPackType GetRtmpPackType() const;

	uint32_t GetBodyDataSize() const;

	void SetBodyDataSize(uint32_t data_size);

	const uint8_t* GetDataSizePtr() const;

	RtmpPackFmt GetFmt() const;

	uint8_t GetCsid() const;

	const uint8_t* GetTimeStamp() const;

	/**
	 * @brief 获取缺少的data字节数
	 * @return
	*/
	uint32_t GetBodyRemainSize() const;

	/**
	 * @brief 获取现在已经保存的的data_长度
	 * @return
	*/
	uint32_t GetBodyCurrentSize() const;

	/**
	 * @brief 追加data数据
	 * @param data data指针
	 * @param length 追加的长度
	*/
	void AppendData(const char* data, size_t length);

	Buffer* GetBuffer();

	/**
	 * 将解析后的header数据 逆向回原数据的16进制表示字符串
	 * @return 44 0 0 f 0 3 4b 8
	 */
	std::string GetHeaderDebugMessage();

private:

	RtmpPackFmt fmt_;
	uint8_t csid_;
	uint8_t timestamp_[3];
	uint8_t data_size_[3];
	RtmpPackType pack_type_;
	uint32_t stream_id_;

	Buffer buffer_;

	const static uint8_t RTMPPACK_FMT_MAX = 3;

	const static uint8_t FMT0_HEADER_LENGTH = 11;
	const static uint8_t FMT1_HEADER_LENGTH = 7;
	const static uint8_t FMT2_HEADER_LENGTH = 3;
	const static uint8_t FMT3_HEADER_LENGTH = 0;

	ssize_t DecodeFmt0(const char* data, size_t length);
	ssize_t DecodeFmt1(const char* data, size_t length);
	ssize_t DecodeFmt2(const char* data, size_t length);

	void SetPackType(uint8_t type);
};

class RtmpCodec
{
public:

	RtmpCodec();
	~RtmpCodec() = default;

	/**
	 * @brief 解析数据存储到 rtmp_pack_中
	 * @param data 数据指针
	 * @param length 数据长度
	 * @param rtmp_pack_ 存储到的包
	 * @return 成功返回解析字节数 失败返回-1 长度不足返回0
	*/
	static ssize_t DecodeHeader(const char* data, size_t length, RtmpPack* rtmp_pack_);

	/**
	 * @brief 将RtmpPack的头部部分 转换到 FlvTag的头部
	 * @return
	*/
	void EncodeHeaderToFlvTag(RtmpPack* rtmp_pack_, FlvTag* flv_tag);

	static void SwapBuffer(RtmpPack* rtmp_pack_, FlvTag* flv_tag);

	void EncodeHeaderAndSwapBuffer(RtmpPack* rtmp_pack_, FlvTag* flv_tag);

	void AddTimeStamp(const uint8_t* timestamp);
private:

	/**
	 * 注意Rtmp包时间戳是相对上一个包的时间戳
	 * 而Flv文件的是第一个FlvTag的时间戳 故需要累加统计
	*/
	union
	{
		uint32_t timestamp_;
		uint8_t ts_[4];
	};
};

#endif // !UTILS_CODEC_RTMPCODEC_H
