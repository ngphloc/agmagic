/*==============================================================*/
/* DBMS name:      Microsoft SQL Server 2000                    */
/* Created on:     12/1/2005 4:44:43 PM                         */
/*==============================================================*/


alter table HBLOCKMATRIX
   drop constraint FK_HMatrix_Images
go


alter table HBLOCKMATRIXINS
   drop constraint FK_HMatrixIns_Images
go


alter table IMAGE256CLRFEATURES
   drop constraint FK_256Clr_Images
go


alter table IMAGE9HSVCLR12TXTFEATURES
   drop constraint FK_ClrTxt_Images
go


alter table IMAGEHBLOCK
   drop constraint FK_HBlock_Images
go


alter table IMAGEHSEG
   drop constraint FK_HSeg_Images
go


alter table IMAGEHSEGINS
   drop constraint FK_HSegIns_Images
go


alter table IMAGEMULTICLRFEATURES
   drop constraint FK_MultiClr_Images
go


alter table IMAGEMULTIFEATURES
   drop constraint FK_MultiFeatures_Images
go


alter table IMAGES
   drop constraint FK_Images_Type
go


alter table IMAGESAFFINITY
   drop constraint FK_Affinity_Images
go


alter table IMAGESAFFINITY
   drop constraint FK_Affinity_Images2
go


alter table IMAGESINFO
   drop constraint FK_Info_Images
go


alter table IMAGESSEMANTIC
   drop constraint FK_ImagesSemantic_Images
go


alter table IMAGESSEMANTIC
   drop constraint FK_ImagesSemantic_Semantic
go


alter table IMAGESSEMANTICWEIGHT
   drop constraint FK_Weight_Images
go


alter table IMAGESSEMANTICWEIGHT
   drop constraint FK_Weight_Semantic
go


alter table IMAGESNORMAFFINITY
   drop constraint FK_NormAff_Images
go


alter table IMAGESNORMAFFINITY
   drop constraint FK_NormAff_Images2
go


alter table SEMANTIC
   drop constraint FK_Semantic_ImagesType
go


alter table SEMANTIC
   drop constraint FK_Semantic_Semantic
go


alter table SEMANTICINFO
   drop constraint FK_SemanticInfo_Semantic
go


alter table USERACCESSFREQ
   drop constraint FK_UserFreq_Images
go


alter table USERACCESSPATTERN
   drop constraint FK_UserPattern_Images
go


alter table USERACCESSPATTERN
   drop constraint FK_UserPattern_Images2
go


if exists (select 1
            from  sysindexes
           where  id    = object_id('IMAGES')
            and   name  = 'IDX_IMAGENAME'
            and   indid > 0
            and   indid < 255)
   drop index IMAGES.IDX_IMAGENAME
go


if exists (select 1
            from  sysobjects
           where  id = object_id('HBLOCKMATRIX')
            and   type = 'U')
   drop table HBLOCKMATRIX
go


if exists (select 1
            from  sysobjects
           where  id = object_id('HBLOCKMATRIXINS')
            and   type = 'U')
   drop table HBLOCKMATRIXINS
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGE256CLRFEATURES')
            and   type = 'U')
   drop table IMAGE256CLRFEATURES
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGE9HSVCLR12TXTFEATURES')
            and   type = 'U')
   drop table IMAGE9HSVCLR12TXTFEATURES
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGEHBLOCK')
            and   type = 'U')
   drop table IMAGEHBLOCK
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGEHSEG')
            and   type = 'U')
   drop table IMAGEHSEG
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGEHSEGINS')
            and   type = 'U')
   drop table IMAGEHSEGINS
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGEMULTICLRFEATURES')
            and   type = 'U')
   drop table IMAGEMULTICLRFEATURES
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGEMULTIFEATURES')
            and   type = 'U')
   drop table IMAGEMULTIFEATURES
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGES')
            and   type = 'U')
   drop table IMAGES
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGESAFFINITY')
            and   type = 'U')
   drop table IMAGESAFFINITY
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGESINFO')
            and   type = 'U')
   drop table IMAGESINFO
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGESSEMANTIC')
            and   type = 'U')
   drop table IMAGESSEMANTIC
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGESSEMANTICWEIGHT')
            and   type = 'U')
   drop table IMAGESSEMANTICWEIGHT
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGESNORMAFFINITY')
            and   type = 'U')
   drop table IMAGESNORMAFFINITY
go


if exists (select 1
            from  sysobjects
           where  id = object_id('IMAGESTYPE')
            and   type = 'U')
   drop table IMAGESTYPE
go


if exists (select 1
            from  sysobjects
           where  id = object_id('SEMANTIC')
            and   type = 'U')
   drop table SEMANTIC
go


if exists (select 1
            from  sysobjects
           where  id = object_id('SEMANTICINFO')
            and   type = 'U')
   drop table SEMANTICINFO
go


if exists (select 1
            from  sysobjects
           where  id = object_id('USERACCESSFREQ')
            and   type = 'U')
   drop table USERACCESSFREQ
go


if exists (select 1
            from  sysobjects
           where  id = object_id('USERACCESSPATTERN')
            and   type = 'U')
   drop table USERACCESSPATTERN
go


/*==============================================================*/
/* Table: HBLOCKMATRIX                                          */
/*==============================================================*/
create table HBLOCKMATRIX (
   IMAGEID              int                  not null,
   ROW                  int                  not null,
   COL                  int                  not null,
   "LEFT"               int                  not null,
   "TOP"                int                  not null,
   "RIGHT"              int                  not null,
   BOTTOM               int                  not null,
   EX                   float                not null,
   CX                   float                not null,
   GRAYLEVEL            float                not null,
   LABEL                int                  not null,
   constraint PK_HBLOCKMATRIX primary key  (IMAGEID, ROW, COL)
)
go


/*==============================================================*/
/* Table: HBLOCKMATRIXINS                                       */
/*==============================================================*/
create table HBLOCKMATRIXINS (
   IMAGEID              int                  not null,
   ROWS                 int                  not null,
   COLS                 int                  not null,
   CX                   int                  null,
   CY                   int                  null,
   HCRUDE               int                  null,
   THRESHOLDEDGE        float                null,
   HEX                  float                null,
   HSJ                  float                null,
   DKR                  float                null,
   HEKCK                float                null,
   constraint PK_HBLOCKMATRIXINS primary key  (IMAGEID)
)
go


/*==============================================================*/
/* Table: IMAGE256CLRFEATURES                                   */
/*==============================================================*/
create table IMAGE256CLRFEATURES (
   IMAGEID              int                  not null,
   CLR0                 float                null,
   CLR1                 float                null,
   CLR2                 float                null,
   CLR3                 float                null,
   CLR4                 float                null,
   CLR5                 float                null,
   CLR6                 float                null,
   CLR7                 float                null,
   CLR8                 float                null,
   CLR9                 float                null,
   CLR10                float                null,
   CLR11                float                null,
   CLR12                float                null,
   CLR13                float                null,
   CLR14                float                null,
   CLR15                float                null,
   CLR16                float                null,
   CLR17                float                null,
   CLR18                float                null,
   CLR19                float                null,
   CLR20                float                null,
   CLR21                float                null,
   CLR22                float                null,
   CLR23                float                null,
   CLR24                float                null,
   CLR25                float                null,
   CLR26                float                null,
   CLR27                float                null,
   CLR28                float                null,
   CLR29                float                null,
   CLR30                float                null,
   CLR31                float                null,
   CLR32                float                null,
   CLR33                float                null,
   CLR34                float                null,
   CLR35                float                null,
   CLR36                float                null,
   CLR37                float                null,
   CLR38                float                null,
   CLR39                float                null,
   CLR40                float                null,
   CLR41                float                null,
   CLR42                float                null,
   CLR43                float                null,
   CLR44                float                null,
   CLR45                float                null,
   CLR46                float                null,
   CLR47                float                null,
   CLR48                float                null,
   CLR49                float                null,
   CLR50                float                null,
   CLR51                float                null,
   CLR52                float                null,
   CLR53                float                null,
   CLR54                float                null,
   CLR55                float                null,
   CLR56                float                null,
   CLR57                float                null,
   CLR58                float                null,
   CLR59                float                null,
   CLR60                float                null,
   CLR61                float                null,
   CLR62                float                null,
   CLR63                float                null,
   CLR64                float                null,
   CLR65                float                null,
   CLR66                float                null,
   CLR67                float                null,
   CLR68                float                null,
   CLR69                float                null,
   CLR70                float                null,
   CLR71                float                null,
   CLR72                float                null,
   CLR73                float                null,
   CLR74                float                null,
   CLR75                float                null,
   CLR76                float                null,
   CLR77                float                null,
   CLR78                float                null,
   CLR79                float                null,
   CLR80                float                null,
   CLR81                float                null,
   CLR82                float                null,
   CLR83                float                null,
   CLR84                float                null,
   CLR85                float                null,
   CLR86                float                null,
   CLR87                float                null,
   CLR88                float                null,
   CLR89                float                null,
   CLR90                float                null,
   CLR91                float                null,
   CLR92                float                null,
   CLR93                float                null,
   CLR94                float                null,
   CLR95                float                null,
   CLR96                float                null,
   CLR97                float                null,
   CLR98                float                null,
   CLR99                float                null,
   CLR100               float                null,
   CLR101               float                null,
   CLR102               float                null,
   CLR103               float                null,
   CLR104               float                null,
   CLR105               float                null,
   CLR106               float                null,
   CLR107               float                null,
   CLR108               float                null,
   CLR109               float                null,
   CLR110               float                null,
   CLR111               float                null,
   CLR112               float                null,
   CLR113               float                null,
   CLR114               float                null,
   CLR115               float                null,
   CLR116               float                null,
   CLR117               float                null,
   CLR118               float                null,
   CLR119               float                null,
   CLR120               float                null,
   CLR121               float                null,
   CLR122               float                null,
   CLR123               float                null,
   CLR124               float                null,
   CLR125               float                null,
   CLR126               float                null,
   CLR127               float                null,
   CLR128               float                null,
   CLR129               float                null,
   CLR130               float                null,
   CLR131               float                null,
   CLR132               float                null,
   CLR133               float                null,
   CLR134               float                null,
   CLR135               float                null,
   CLR136               float                null,
   CLR137               float                null,
   CLR138               float                null,
   CLR139               float                null,
   CLR140               float                null,
   CLR141               float                null,
   CLR142               float                null,
   CLR143               float                null,
   CLR144               float                null,
   CLR145               float                null,
   CLR146               float                null,
   CLR147               float                null,
   CLR148               float                null,
   CLR149               float                null,
   CLR150               float                null,
   CLR151               float                null,
   CLR152               float                null,
   CLR153               float                null,
   CLR154               float                null,
   CLR155               float                null,
   CLR156               float                null,
   CLR157               float                null,
   CLR158               float                null,
   CLR159               float                null,
   CLR160               float                null,
   CLR161               float                null,
   CLR162               float                null,
   CLR163               float                null,
   CLR164               float                null,
   CLR165               float                null,
   CLR166               float                null,
   CLR167               float                null,
   CLR168               float                null,
   CLR169               float                null,
   CLR170               float                null,
   CLR171               float                null,
   CLR172               float                null,
   CLR173               float                null,
   CLR174               float                null,
   CLR175               float                null,
   CLR176               float                null,
   CLR177               float                null,
   CLR178               float                null,
   CLR179               float                null,
   CLR180               float                null,
   CLR181               float                null,
   CLR182               float                null,
   CLR183               float                null,
   CLR184               float                null,
   CLR185               float                null,
   CLR186               float                null,
   CLR187               float                null,
   CLR188               float                null,
   CLR189               float                null,
   CLR190               float                null,
   CLR191               float                null,
   CLR192               float                null,
   CLR193               float                null,
   CLR194               float                null,
   CLR195               float                null,
   CLR196               float                null,
   CLR197               float                null,
   CLR198               float                null,
   CLR199               float                null,
   CLR200               float                null,
   CLR201               float                null,
   CLR202               float                null,
   CLR203               float                null,
   CLR204               float                null,
   CLR205               float                null,
   CLR206               float                null,
   CLR207               float                null,
   CLR208               float                null,
   CLR209               float                null,
   CLR210               float                null,
   CLR211               float                null,
   CLR212               float                null,
   CLR213               float                null,
   CLR214               float                null,
   CLR215               float                null,
   CLR216               float                null,
   CLR217               float                null,
   CLR218               float                null,
   CLR219               float                null,
   CLR220               float                null,
   CLR221               float                null,
   CLR222               float                null,
   CLR223               float                null,
   CLR224               float                null,
   CLR225               float                null,
   CLR226               float                null,
   CLR227               float                null,
   CLR228               float                null,
   CLR229               float                null,
   CLR230               float                null,
   CLR231               float                null,
   CLR232               float                null,
   CLR233               float                null,
   CLR234               float                null,
   CLR235               float                null,
   CLR236               float                null,
   CLR237               float                null,
   CLR238               float                null,
   CLR239               float                null,
   CLR240               float                null,
   CLR241               float                null,
   CLR242               float                null,
   CLR243               float                null,
   CLR244               float                null,
   CLR245               float                null,
   CLR246               float                null,
   CLR247               float                null,
   CLR248               float                null,
   CLR249               float                null,
   CLR250               float                null,
   CLR251               float                null,
   CLR252               float                null,
   CLR253               float                null,
   CLR254               float                null,
   CLR255               float                null,
   constraint PK_256Clr primary key  (IMAGEID)
)
go


/*==============================================================*/
/* Table: IMAGE9HSVCLR12TXTFEATURES                                   */
/*==============================================================*/
create table IMAGE9HSVCLR12TXTFEATURES (
   IMAGEID              int                  not null,
   BLACK                float                null,
   W                    float                null,
   RED                  float                null,
   RY                   float                null,
   Y                    float                null,
   YG                   float                null,
   G                    float                null,
   GB                   float                null,
   B                    float                null,
   BP                   float                null,
   P                    float                null,
   PR                   float                null,
   L1                   float                null,
   L2                   float                null,
   L3                   float                null,
   L4                   float                null,
   L5                   float                null,
   L6                   float                null,
   L7                   float                null,
   L8                   float                null,
   L9                   float                null,
   constraint PK_ClrTxt primary key  (IMAGEID)
)
go


/*==============================================================*/
/* Table: IMAGEHBLOCK                                           */
/*==============================================================*/
create table IMAGEHBLOCK (
   IMAGEID              int                  not null,
   LABEL                int                  not null,
   IDX                  int                  not null,
   LBOUND               int                  null,
   TBOUND               int                  null,
   RBOUND               int                  null,
   BBOUND               int                  null,
   EX                   float                null,
   CX                   float                null,
   GRAYLEVEL            float                null,
   constraint PK_IMAGEHBLOCK primary key  (IMAGEID, LABEL, IDX)
)
go


/*==============================================================*/
/* Table: IMAGEHSEG                                             */
/*==============================================================*/
create table IMAGEHSEG (
   IMAGEID              int                  not null,
   LABEL                int                  not null,
   NBLOCKS              int                  not null,
   NTOTALPIXELS         int                  null,
   LBOUND               int                  null,
   TBOUND               int                  null,
   RBOUND               int                  null,
   BBOUND               int                  null,
   constraint PK_IMAGEHSEG primary key  (IMAGEID, LABEL)
)
go


/*==============================================================*/
/* Table: IMAGEHSEGINS                                          */
/*==============================================================*/
create table IMAGEHSEGINS (
   IMAGEID              int                  not null,
   NSEGS                int                  not null,
   LBOUND               int                  null,
   TBOUND               int                  null,
   RBOUND               int                  null,
   BBOUND               int                  null,
   constraint PK_IMAGEHSEGINS primary key  (IMAGEID)
)
go


/*==============================================================*/
/* Table: IMAGEMULTICLRFEATURES                                 */
/*==============================================================*/
create table IMAGEMULTICLRFEATURES (
   IMAGEID              int                  not null,
   COMPONENT            int                  not null,
   CLR0                 float                null,
   CLR1                 float                null,
   CLR2                 float                null,
   CLR3                 float                null,
   CLR4                 float                null,
   CLR5                 float                null,
   CLR6                 float                null,
   CLR7                 float                null,
   CLR8                 float                null,
   CLR9                 float                null,
   CLR10                float                null,
   CLR11                float                null,
   CLR12                float                null,
   CLR13                float                null,
   CLR14                float                null,
   CLR15                float                null,
   CLR16                float                null,
   CLR17                float                null,
   CLR18                float                null,
   CLR19                float                null,
   CLR20                float                null,
   CLR21                float                null,
   CLR22                float                null,
   CLR23                float                null,
   CLR24                float                null,
   CLR25                float                null,
   CLR26                float                null,
   CLR27                float                null,
   CLR28                float                null,
   CLR29                float                null,
   CLR30                float                null,
   CLR31                float                null,
   CLR32                float                null,
   CLR33                float                null,
   CLR34                float                null,
   CLR35                float                null,
   CLR36                float                null,
   CLR37                float                null,
   CLR38                float                null,
   CLR39                float                null,
   CLR40                float                null,
   CLR41                float                null,
   CLR42                float                null,
   CLR43                float                null,
   CLR44                float                null,
   CLR45                float                null,
   CLR46                float                null,
   CLR47                float                null,
   CLR48                float                null,
   CLR49                float                null,
   CLR50                float                null,
   CLR51                float                null,
   CLR52                float                null,
   CLR53                float                null,
   CLR54                float                null,
   CLR55                float                null,
   CLR56                float                null,
   CLR57                float                null,
   CLR58                float                null,
   CLR59                float                null,
   CLR60                float                null,
   CLR61                float                null,
   CLR62                float                null,
   CLR63                float                null,
   CLR64                float                null,
   CLR65                float                null,
   CLR66                float                null,
   CLR67                float                null,
   CLR68                float                null,
   CLR69                float                null,
   CLR70                float                null,
   CLR71                float                null,
   CLR72                float                null,
   CLR73                float                null,
   CLR74                float                null,
   CLR75                float                null,
   CLR76                float                null,
   CLR77                float                null,
   CLR78                float                null,
   CLR79                float                null,
   CLR80                float                null,
   CLR81                float                null,
   CLR82                float                null,
   CLR83                float                null,
   CLR84                float                null,
   CLR85                float                null,
   CLR86                float                null,
   CLR87                float                null,
   CLR88                float                null,
   CLR89                float                null,
   CLR90                float                null,
   CLR91                float                null,
   CLR92                float                null,
   CLR93                float                null,
   CLR94                float                null,
   CLR95                float                null,
   CLR96                float                null,
   CLR97                float                null,
   CLR98                float                null,
   CLR99                float                null,
   CLR100               float                null,
   CLR101               float                null,
   CLR102               float                null,
   CLR103               float                null,
   CLR104               float                null,
   CLR105               float                null,
   CLR106               float                null,
   CLR107               float                null,
   CLR108               float                null,
   CLR109               float                null,
   CLR110               float                null,
   CLR111               float                null,
   CLR112               float                null,
   CLR113               float                null,
   CLR114               float                null,
   CLR115               float                null,
   CLR116               float                null,
   CLR117               float                null,
   CLR118               float                null,
   CLR119               float                null,
   CLR120               float                null,
   CLR121               float                null,
   CLR122               float                null,
   CLR123               float                null,
   CLR124               float                null,
   CLR125               float                null,
   CLR126               float                null,
   CLR127               float                null,
   CLR128               float                null,
   CLR129               float                null,
   CLR130               float                null,
   CLR131               float                null,
   CLR132               float                null,
   CLR133               float                null,
   CLR134               float                null,
   CLR135               float                null,
   CLR136               float                null,
   CLR137               float                null,
   CLR138               float                null,
   CLR139               float                null,
   CLR140               float                null,
   CLR141               float                null,
   CLR142               float                null,
   CLR143               float                null,
   CLR144               float                null,
   CLR145               float                null,
   CLR146               float                null,
   CLR147               float                null,
   CLR148               float                null,
   CLR149               float                null,
   CLR150               float                null,
   CLR151               float                null,
   CLR152               float                null,
   CLR153               float                null,
   CLR154               float                null,
   CLR155               float                null,
   CLR156               float                null,
   CLR157               float                null,
   CLR158               float                null,
   CLR159               float                null,
   CLR160               float                null,
   CLR161               float                null,
   CLR162               float                null,
   CLR163               float                null,
   CLR164               float                null,
   CLR165               float                null,
   CLR166               float                null,
   CLR167               float                null,
   CLR168               float                null,
   CLR169               float                null,
   CLR170               float                null,
   CLR171               float                null,
   CLR172               float                null,
   CLR173               float                null,
   CLR174               float                null,
   CLR175               float                null,
   CLR176               float                null,
   CLR177               float                null,
   CLR178               float                null,
   CLR179               float                null,
   CLR180               float                null,
   CLR181               float                null,
   CLR182               float                null,
   CLR183               float                null,
   CLR184               float                null,
   CLR185               float                null,
   CLR186               float                null,
   CLR187               float                null,
   CLR188               float                null,
   CLR189               float                null,
   CLR190               float                null,
   CLR191               float                null,
   CLR192               float                null,
   CLR193               float                null,
   CLR194               float                null,
   CLR195               float                null,
   CLR196               float                null,
   CLR197               float                null,
   CLR198               float                null,
   CLR199               float                null,
   CLR200               float                null,
   CLR201               float                null,
   CLR202               float                null,
   CLR203               float                null,
   CLR204               float                null,
   CLR205               float                null,
   CLR206               float                null,
   CLR207               float                null,
   CLR208               float                null,
   CLR209               float                null,
   CLR210               float                null,
   CLR211               float                null,
   CLR212               float                null,
   CLR213               float                null,
   CLR214               float                null,
   CLR215               float                null,
   CLR216               float                null,
   CLR217               float                null,
   CLR218               float                null,
   CLR219               float                null,
   CLR220               float                null,
   CLR221               float                null,
   CLR222               float                null,
   CLR223               float                null,
   CLR224               float                null,
   CLR225               float                null,
   CLR226               float                null,
   CLR227               float                null,
   CLR228               float                null,
   CLR229               float                null,
   CLR230               float                null,
   CLR231               float                null,
   CLR232               float                null,
   CLR233               float                null,
   CLR234               float                null,
   CLR235               float                null,
   CLR236               float                null,
   CLR237               float                null,
   CLR238               float                null,
   CLR239               float                null,
   CLR240               float                null,
   CLR241               float                null,
   CLR242               float                null,
   CLR243               float                null,
   CLR244               float                null,
   CLR245               float                null,
   CLR246               float                null,
   CLR247               float                null,
   CLR248               float                null,
   CLR249               float                null,
   CLR250               float                null,
   CLR251               float                null,
   CLR252               float                null,
   CLR253               float                null,
   CLR254               float                null,
   CLR255               float                null,
   constraint PK_MultiClr primary key  (IMAGEID, COMPONENT)
)
go


/*==============================================================*/
/* Table: IMAGEMULTIFEATURES                                    */
/*==============================================================*/
create table IMAGEMULTIFEATURES (
   IMAGEID              int                  not null,
   COMPONENT            int                  not null,
   NUMATT               int                  not null,
   ATT0                 float                null,
   ATT1                 float                null,
   ATT2                 float                null,
   ATT3                 float                null,
   ATT4                 float                null,
   ATT5                 float                null,
   ATT6                 float                null,
   ATT7                 float                null,
   ATT8                 float                null,
   ATT9                 float                null,
   ATT10                float                null,
   ATT11                float                null,
   ATT12                float                null,
   ATT13                float                null,
   ATT14                float                null,
   ATT15                float                null,
   ATT16                float                null,
   ATT17                float                null,
   ATT18                float                null,
   ATT19                float                null,
   ATT20                float                null,
   ATT21                float                null,
   ATT22                float                null,
   ATT23                float                null,
   ATT24                float                null,
   ATT25                float                null,
   ATT26                float                null,
   ATT27                float                null,
   ATT28                float                null,
   ATT29                float                null,
   ATT30                float                null,
   ATT31                float                null,
   ATT32                float                null,
   ATT33                float                null,
   ATT34                float                null,
   ATT35                float                null,
   ATT36                float                null,
   ATT37                float                null,
   ATT38                float                null,
   ATT39                float                null,
   ATT40                float                null,
   ATT41                float                null,
   ATT42                float                null,
   ATT43                float                null,
   ATT44                float                null,
   ATT45                float                null,
   ATT46                float                null,
   ATT47                float                null,
   ATT48                float                null,
   ATT49                float                null,
   ATT50                float                null,
   ATT51                float                null,
   ATT52                float                null,
   ATT53                float                null,
   ATT54                float                null,
   ATT55                float                null,
   ATT56                float                null,
   ATT57                float                null,
   ATT58                float                null,
   ATT59                float                null,
   ATT60                float                null,
   ATT61                float                null,
   ATT62                float                null,
   ATT63                float                null,
   ATT64                float                null,
   ATT65                float                null,
   ATT66                float                null,
   ATT67                float                null,
   ATT68                float                null,
   ATT69                float                null,
   ATT70                float                null,
   ATT71                float                null,
   ATT72                float                null,
   ATT73                float                null,
   ATT74                float                null,
   ATT75                float                null,
   ATT76                float                null,
   ATT77                float                null,
   ATT78                float                null,
   ATT79                float                null,
   ATT80                float                null,
   ATT81                float                null,
   ATT82                float                null,
   ATT83                float                null,
   ATT84                float                null,
   ATT85                float                null,
   ATT86                float                null,
   ATT87                float                null,
   ATT88                float                null,
   ATT89                float                null,
   ATT90                float                null,
   ATT91                float                null,
   ATT92                float                null,
   ATT93                float                null,
   ATT94                float                null,
   ATT95                float                null,
   ATT96                float                null,
   ATT97                float                null,
   ATT98                float                null,
   ATT99                float                null,
   ATT100               float                null,
   ATT101               float                null,
   ATT102               float                null,
   ATT103               float                null,
   ATT104               float                null,
   ATT105               float                null,
   ATT106               float                null,
   ATT107               float                null,
   ATT108               float                null,
   ATT109               float                null,
   ATT110               float                null,
   ATT111               float                null,
   ATT112               float                null,
   ATT113               float                null,
   ATT114               float                null,
   ATT115               float                null,
   ATT116               float                null,
   ATT117               float                null,
   ATT118               float                null,
   ATT119               float                null,
   ATT120               float                null,
   ATT121               float                null,
   ATT122               float                null,
   ATT123               float                null,
   ATT124               float                null,
   ATT125               float                null,
   ATT126               float                null,
   ATT127               float                null,
   ATT128               float                null,
   ATT129               float                null,
   ATT130               float                null,
   ATT131               float                null,
   ATT132               float                null,
   ATT133               float                null,
   ATT134               float                null,
   ATT135               float                null,
   ATT136               float                null,
   ATT137               float                null,
   ATT138               float                null,
   ATT139               float                null,
   ATT140               float                null,
   ATT141               float                null,
   ATT142               float                null,
   ATT143               float                null,
   ATT144               float                null,
   ATT145               float                null,
   ATT146               float                null,
   ATT147               float                null,
   ATT148               float                null,
   ATT149               float                null,
   ATT150               float                null,
   ATT151               float                null,
   ATT152               float                null,
   ATT153               float                null,
   ATT154               float                null,
   ATT155               float                null,
   ATT156               float                null,
   ATT157               float                null,
   ATT158               float                null,
   ATT159               float                null,
   ATT160               float                null,
   ATT161               float                null,
   ATT162               float                null,
   ATT163               float                null,
   ATT164               float                null,
   ATT165               float                null,
   ATT166               float                null,
   ATT167               float                null,
   ATT168               float                null,
   ATT169               float                null,
   ATT170               float                null,
   ATT171               float                null,
   ATT172               float                null,
   ATT173               float                null,
   ATT174               float                null,
   ATT175               float                null,
   ATT176               float                null,
   ATT177               float                null,
   ATT178               float                null,
   ATT179               float                null,
   ATT180               float                null,
   ATT181               float                null,
   ATT182               float                null,
   ATT183               float                null,
   ATT184               float                null,
   ATT185               float                null,
   ATT186               float                null,
   ATT187               float                null,
   ATT188               float                null,
   ATT189               float                null,
   ATT190               float                null,
   ATT191               float                null,
   ATT192               float                null,
   ATT193               float                null,
   ATT194               float                null,
   ATT195               float                null,
   ATT196               float                null,
   ATT197               float                null,
   ATT198               float                null,
   ATT199               float                null,
   ATT200               float                null,
   ATT201               float                null,
   ATT202               float                null,
   ATT203               float                null,
   ATT204               float                null,
   ATT205               float                null,
   ATT206               float                null,
   ATT207               float                null,
   ATT208               float                null,
   ATT209               float                null,
   ATT210               float                null,
   ATT211               float                null,
   ATT212               float                null,
   ATT213               float                null,
   ATT214               float                null,
   ATT215               float                null,
   ATT216               float                null,
   ATT217               float                null,
   ATT218               float                null,
   ATT219               float                null,
   ATT220               float                null,
   ATT221               float                null,
   ATT222               float                null,
   ATT223               float                null,
   ATT224               float                null,
   ATT225               float                null,
   ATT226               float                null,
   ATT227               float                null,
   ATT228               float                null,
   ATT229               float                null,
   ATT230               float                null,
   ATT231               float                null,
   ATT232               float                null,
   ATT233               float                null,
   ATT234               float                null,
   ATT235               float                null,
   ATT236               float                null,
   ATT237               float                null,
   ATT238               float                null,
   ATT239               float                null,
   ATT240               float                null,
   ATT241               float                null,
   ATT242               float                null,
   ATT243               float                null,
   ATT244               float                null,
   ATT245               float                null,
   ATT246               float                null,
   ATT247               float                null,
   ATT248               float                null,
   ATT249               float                null,
   ATT250               float                null,
   ATT251               float                null,
   ATT252               float                null,
   ATT253               float                null,
   ATT254               float                null,
   ATT255               float                null,
   constraint PK_MultiFeatures primary key  (IMAGEID, COMPONENT)
)
go


/*==============================================================*/
/* Table: IMAGES                                                */
/*==============================================================*/
create table IMAGES (
   ID                   int                  identity,
   TYPE                 int                  null,
   NAME                 nvarchar(255)        null,
   URL                  nvarchar(1024)       null,
   constraint PK_Image primary key  (ID)
)
go


/*==============================================================*/
/* Index: IDX_IMAGENAME                                         */
/*==============================================================*/
create   index IDX_IMAGENAME on IMAGES (
NAME
)
go


/*==============================================================*/
/* Table: IMAGESAFFINITY                                        */
/*==============================================================*/
create table IMAGESAFFINITY (
   IMAGEID              int                  not null,
   RELATEDIMAGEID       int                  not null,
   MEASURE              float                not null,
   constraint PK_Affinity primary key  (IMAGEID, RELATEDIMAGEID)
)
go


/*==============================================================*/
/* Table: IMAGESINFO                                            */
/*==============================================================*/
create table IMAGESINFO (
   IMAGEID              int                  not null,
   AUTHOR               nvarchar(255)        null,
   constraint PK_IMAGESINFO primary key  (IMAGEID)
)
go


/*==============================================================*/
/* Table: IMAGESSEMANTIC                                        */
/*==============================================================*/
create table IMAGESSEMANTIC (
   IMAGEID              int                  not null,
   SEMANTICID           int                  not null,
   constraint PK_IMAGESSEMANTIC primary key  (IMAGEID, SEMANTICID)
)
go


/*==============================================================*/
/* Table: IMAGESSEMANTICWEIGHT                                  */
/*==============================================================*/
create table IMAGESSEMANTICWEIGHT (
   IMAGEID              int                  not null,
   SEMANTICID           int                  not null,
   WEIGHT               float                not null,
   constraint PK_IMAGESSEMANTICWEIGHT primary key  (IMAGEID, SEMANTICID)
)
go


/*==============================================================*/
/* Table: IMAGESNORMAFFINITY                                     */
/*==============================================================*/
create table IMAGESNORMAFFINITY (
   IMAGEID              int                  not null,
   RELATEDIMAGEID       int                  not null,
   MEASURE              float                null,
   constraint PK_NormAff primary key  (IMAGEID, RELATEDIMAGEID)
)
go


/*==============================================================*/
/* Table: IMAGESTYPE                                            */
/*==============================================================*/
create table IMAGESTYPE (
   ID                   int                  not null,
   DESCRIPTION          nvarchar(255)        null,
   constraint PK_IMAGESTYPE primary key  (ID)
)
go


/*==============================================================*/
/* Table: SEMANTIC                                              */
/*==============================================================*/
create table SEMANTIC (
   ID                   int                  identity,
   NAME                 nvarchar(255)        null,
   PARENTID             int                  null,
   IMAGETYPE            int                  null,
   constraint PK_SEMANTIC primary key  (ID)
)
go


/*==============================================================*/
/* Table: SEMANTICINFO                                          */
/*==============================================================*/
create table SEMANTICINFO (
   SEMANTICID           int                  not null,
   DESCS                nvarchar(255)        null,
   constraint PK_SEMANTICINFO primary key  (SEMANTICID)
)
go


/*==============================================================*/
/* Table: USERACCESSFREQ                                        */
/*==============================================================*/
create table USERACCESSFREQ (
   IMAGEID              int                  not null,
   TACCESSED            numeric              not null,
   NACCESSED            int                  null,
   constraint PK_UserFreq primary key  (IMAGEID, TACCESSED)
)
go


/*==============================================================*/
/* Table: USERACCESSPATTERN                                     */
/*==============================================================*/
create table USERACCESSPATTERN (
   IMAGEID              int                  not null,
   RELATEDIMAGEID       int                  not null,
   TACCESSED            numeric              not null,
   ISACCESSED           int                  null,
   constraint PK_UserPattern primary key  (IMAGEID, RELATEDIMAGEID, TACCESSED)
)
go


alter table HBLOCKMATRIX
   add constraint FK_HMatrix_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table HBLOCKMATRIXINS
   add constraint FK_HMatrixIns_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGE256CLRFEATURES
   add constraint FK_256Clr_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGE9HSVCLR12TXTFEATURES
   add constraint FK_ClrTxt_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGEHBLOCK
   add constraint FK_HBlock_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGEHSEG
   add constraint FK_HSeg_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGEHSEGINS
   add constraint FK_HSegIns_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGEMULTICLRFEATURES
   add constraint FK_MultiClr_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGEMULTIFEATURES
   add constraint FK_MultiFeatures_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGES
   add constraint FK_Images_Type foreign key (TYPE)
      references IMAGESTYPE (ID)
      on update cascade on delete cascade
go


alter table IMAGESAFFINITY
   add constraint FK_Affinity_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGESAFFINITY
   add constraint FK_Affinity_Images2 foreign key (RELATEDIMAGEID)
      references IMAGES (ID)
go


alter table IMAGESINFO
   add constraint FK_Info_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGESSEMANTIC
   add constraint FK_ImagesSemantic_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGESSEMANTIC
   add constraint FK_ImagesSemantic_Semantic foreign key (SEMANTICID)
      references SEMANTIC (ID)
      on update cascade on delete cascade
go


alter table IMAGESSEMANTICWEIGHT
   add constraint FK_Weight_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGESSEMANTICWEIGHT
   add constraint FK_Weight_Semantic foreign key (SEMANTICID)
      references SEMANTIC (ID)
      on update cascade on delete cascade
go


alter table IMAGESNORMAFFINITY
   add constraint FK_NormAff_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table IMAGESNORMAFFINITY
   add constraint FK_NormAff_Images2 foreign key (RELATEDIMAGEID)
      references IMAGES (ID)
go


alter table SEMANTIC
   add constraint FK_Semantic_ImagesType foreign key (IMAGETYPE)
      references IMAGESTYPE (ID)
go


alter table SEMANTIC
   add constraint FK_Semantic_Semantic foreign key (PARENTID)
      references SEMANTIC (ID)
go


alter table SEMANTICINFO
   add constraint FK_SemanticInfo_Semantic foreign key (SEMANTICID)
      references SEMANTIC (ID)
      on update cascade on delete cascade
go


alter table USERACCESSFREQ
   add constraint FK_UserFreq_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table USERACCESSPATTERN
   add constraint FK_UserPattern_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade
go


alter table USERACCESSPATTERN
   add constraint FK_UserPattern_Images2 foreign key (RELATEDIMAGEID)
      references IMAGES (ID)
go


