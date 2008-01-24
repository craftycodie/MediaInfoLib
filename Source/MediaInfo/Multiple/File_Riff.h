// File_Riff - Info for RIFF files
// Copyright (C) 2002-2008 Jerome Martinez, Zen@MediaArea.net
//
// This library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// Information about RIFF files
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//---------------------------------------------------------------------------
#ifndef MediaInfo_File_RiffH
#define MediaInfo_File_RiffH
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "MediaInfo/File__Analyze.h"
#include <vector>
//---------------------------------------------------------------------------

namespace MediaInfoLib
{

//***************************************************************************
// Class File_Riff
//***************************************************************************

class File_Riff : public File__Analyze
{
protected :
    //Format
    void Read_Buffer_Finalize ();

    //Information
    void HowTo (stream_t StreamKind);

public :
    File_Riff();

private :
    //Buffer
    void Header_Parse();
    void Data_Parse();
    bool BookMark_Needed();
    
    //Data
    struct stream
    {
        File__Analyze*          Parser;
        int32u                  fccType;
        int32u                  fccHandler;
        int32u                  Compression;
        stream_t                StreamKind;
        size_t                  StreamPos;
        int32u                  AvgBytesPerSec;
        size_t                  PacketCount;
        int64u                  StreamSize;
        bool                    SearchingPayload;
        bool                    Specific_IsMpeg4v;

        stream()
        {
            Parser=NULL;
            fccType=0x00000000;
            fccHandler=0x00000000;
            Compression=0x00000000;
            StreamKind=Stream_Max;
            StreamPos=0;
            AvgBytesPerSec=0;
            PacketCount=0;
            StreamSize=0;
            SearchingPayload=true;
            Specific_IsMpeg4v=false;
        }

        ~stream()
        {
            delete Parser; //Parser=NULL;
        }
    };
    std::map<int32u, stream> Stream;
    int32u                   Stream_ID;

    std::map<int64u, int64u> Stream_Pos;
    std::map<int64u, int64u> Index_Pos;
    std::map<int64u, int64u>::iterator Stream_Pos_Current;
    std::map<int64u, int64u>::iterator Index_Pos_Current;
    int64u Interleaved0_1;
    int64u Interleaved0_10;
    int64u Interleaved1_1;
    int64u Interleaved1_10;

    //Temp
    float64 avih_FrameRate; //FrameRate of the first video stream in one MOVI chunk
    int32u avih_TotalFrame; //Count of frames in one MOVI chunk
    int32u dmlh_TotalFrame; //Count of frames in the whole AVI file (with odml too)
    int64u movi_Pos;        //Pos of the data part (AVI)
    int64u movi_Size;       //Size of the data part (AVI and AVIX)
    int8u  stream_Count;    //How many stream we have to parse
    bool   rec__Present;    //True if synchro element is present
    bool   Alignement_ExtraByte;
    bool   NeedOldIndex;
    bool   IsBigEndian;
    bool   IsOpenDML;

    //Chunks
    void AIFC ();
    void AIFC_COMM ();
    void AIFC_COMT ();
    void AIFC_FVER ();
    void AIFC_SSND ();
    void AIFC_xxxx ();
    void AIFF ();
    void AIFF_COMM ();
    void AIFF_COMT ();
    void AIFF_SSND ();
    void AIFF_xxxx ();
    void AVI_ ();
    void AVI__cset ();
    void AVI__exif ();
    void AVI__exif_xxxx ();
    void AVI__GMET ();
    void AVI__goog ();
    void AVI__goog_GDAT ();
    void AVI__hdlr ();
    void AVI__hdlr_avih ();
    void AVI__hdlr_JUNK ();
    void AVI__hdlr_strl ();
    void AVI__hdlr_strl_indx ();
    void AVI__hdlr_strl_indx_StandardIndex (int32u Entry_Count, int32u ChunkId);
    void AVI__hdlr_strl_indx_FieldIndex (int32u Entry_Count, int32u ChunkId);
    void AVI__hdlr_strl_indx_SuperIndex (int32u Entry_Count, int32u ChunkId);
    void AVI__hdlr_strl_JUNK ();
    void AVI__hdlr_strl_strd ();
    void AVI__hdlr_strl_strf ();
    void AVI__hdlr_strl_strf_auds ();
    void AVI__hdlr_strl_strf_auds_Mpega();
    void AVI__hdlr_strl_strf_auds_Aac();
    void AVI__hdlr_strl_strf_iavs ();
    void AVI__hdlr_strl_strf_mids ();
    void AVI__hdlr_strl_strf_txts ();
    void AVI__hdlr_strl_strf_vids ();
    void AVI__hdlr_strl_strh ();
    void AVI__hdlr_strl_strn ();
    void AVI__hdlr_strl_vprp ();
    void AVI__hdlr_odml ();
    void AVI__hdlr_odml_dmlh ();
    void AVI__hdlr_xxxx ();
    void AVI__idx1 ();
    void AVI__INFO ();
    void AVI__INFO_JUNK ();
    void AVI__INFO_xxxx ();
    void AVI__JUNK ();
    void AVI__movi ();
    void AVI__movi_xxxx ();
    void AVI__movi_xxxx___dc ();
    void AVI__movi_xxxx___sb ();
    void AVI__movi_xxxx___tx ();
    void AVI__movi_xxxx___wb ();
    void AVI__movi_rec_ ();
    void AVI__movi_rec__xxxx ();
    void AVI__movi_StreamJump ();
    void AVI__movi_StreamClear (int32u ChunkId);
    void AVI__ULSC ();
    void AVI__uvio ();
    void AVIX ();
    void AVIX_idx1 ();
    void AVIX_movi ();
    void AVIX_movi_xxxx ();
    void AVIX_movi_rec_ ();
    void AVIX_movi_rec__xxxx ();
    void menu ();
    void MThd ();
    void MTrk ();
    void PAL_ ();
    void RDIB ();
    void RMID ();
    void RMMP ();
    void IDVX ();
    void WAVE ();
    void WAVE_data ();
    void WAVE_fact ();
    void WAVE_fmt_ ();
    void W3DI();
};

} //NameSpace

#endif
