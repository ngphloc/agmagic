/*==============================================================*/
/* DBMS name:      Microsoft Access 2000                        */
/* Created on:     12/1/2005 4:54:42 PM                         */
/*==============================================================*/


alter table HBLOCKMATRIX
   drop constraint FK_HMatrix_Images;

alter table HBLOCKMATRIXINS
   drop constraint FK_HMatrixIns_Images;

alter table IMAGE9HSVCLR12TXTFEATURES
   drop constraint FK_ClrTxt_Images;

alter table IMAGEHBLOCK
   drop constraint FK_HBlock_Images;

alter table IMAGEHSEG
   drop constraint FK_HSeg_Images;

alter table IMAGEHSEGINS
   drop constraint FK_HSegIns_Images;

alter table IMAGES
   drop constraint FK_Images_Type;

alter table IMAGESAFFINITY
   drop constraint FK_Affinity_Images;

alter table IMAGESAFFINITY
   drop constraint FK_Affinity_Images2;

alter table IMAGESINFO
   drop constraint FK_Info_Images;

alter table IMAGESSEMANTIC
   drop constraint FK_ImagesSemantic_Images;

alter table IMAGESSEMANTIC
   drop constraint FK_ImagesSemantic_Semantic;

alter table IMAGESSEMANTICWEIGHT
   drop constraint FK_Weight_Images;

alter table IMAGESSEMANTICWEIGHT
   drop constraint FK_Weight_Semantic;

alter table IMAGESNORMAFFINITY
   drop constraint FK_NormAff_Images;

alter table IMAGESNORMAFFINITY
   drop constraint FK_NormAff_Images2;

alter table SEMANTIC
   drop constraint FK_Semantic_ImagesType;

alter table SEMANTIC
   drop constraint FK_Semantic_Semantic;

alter table SEMANTICINFO
   drop constraint FK_SemanticInfo_Semantic;

alter table USERACCESSFREQ
   drop constraint FK_UserFreq_Images;

alter table USERACCESSPATTERN
   drop constraint FK_UserPattern_Images;

alter table USERACCESSPATTERN
   drop constraint FK_UserPattern_Images2;

drop index IDX_IMAGENAME on IMAGES;

drop table HBLOCKMATRIX;

drop table HBLOCKMATRIXINS;

drop table IMAGE9HSVCLR12TXTFEATURES;

drop table IMAGEHBLOCK;

drop table IMAGEHSEG;

drop table IMAGEHSEGINS;

drop table IMAGES;

drop table IMAGESAFFINITY;

drop table IMAGESINFO;

drop table IMAGESSEMANTIC;

drop table IMAGESSEMANTICWEIGHT;

drop table IMAGESNORMAFFINITY;

drop table IMAGESTYPE;

drop table SEMANTIC;

drop table SEMANTICINFO;

drop table USERACCESSFREQ;

drop table USERACCESSPATTERN;

/*==============================================================*/
/* Table: HBLOCKMATRIX                                          */
/*==============================================================*/
create table HBLOCKMATRIX
(
    IMAGEID              INTEGER         not null,
    ROW                  INTEGER         not null,
    COL                  INTEGER         not null,
    LEFT                 INTEGER         not null,
    TOP                  INTEGER         not null,
    RIGHT                INTEGER         not null,
    BOTTOM               INTEGER         not null,
    EX                   FLOAT           not null,
    CX                   FLOAT           not null,
    GRAYLEVEL            FLOAT           not null,
    LABEL                INTEGER         not null,
constraint PK_HBLOCKMATRIX primary key (IMAGEID, ROW, COL)
);

/*==============================================================*/
/* Table: HBLOCKMATRIXINS                                       */
/*==============================================================*/
create table HBLOCKMATRIXINS
(
    IMAGEID              INTEGER         not null,
    "ROWS"               INTEGER         not null,
    COLS                 INTEGER         not null,
    CX                   INTEGER,
    CY                   INTEGER,
    HCRUDE               INTEGER,
    THRESHOLDEDGE        FLOAT,
    HEX                  FLOAT,
    HSJ                  FLOAT,
    DKR                  FLOAT,
    HEKCK                FLOAT,
constraint PK_HBLOCKMATRIXINS primary key (IMAGEID)
);

/*==============================================================*/
/* Table: IMAGE9HSVCLR12TXTFEATURES                                   */
/*==============================================================*/
create table IMAGE9HSVCLR12TXTFEATURES
(
    IMAGEID              INTEGER         not null,
    BLACK                FLOAT,
    W                    FLOAT,
    RED                  FLOAT,
    RY                   FLOAT,
    Y                    FLOAT,
    YG                   FLOAT,
    G                    FLOAT,
    GB                   FLOAT,
    B                    FLOAT,
    BP                   FLOAT,
    P                    FLOAT,
    PR                   FLOAT,
    L1                   FLOAT,
    L2                   FLOAT,
    L3                   FLOAT,
    L4                   FLOAT,
    L5                   FLOAT,
    L6                   FLOAT,
    L7                   FLOAT,
    L8                   FLOAT,
    L9                   FLOAT,
constraint PK_ClrTxt primary key (IMAGEID)
);

/*==============================================================*/
/* Table: IMAGEHBLOCK                                           */
/*==============================================================*/
create table IMAGEHBLOCK
(
    IMAGEID              INTEGER         not null,
    LABEL                INTEGER         not null,
    IDX                  INTEGER         not null,
    LBOUND               INTEGER,
    TBOUND               INTEGER,
    RBOUND               INTEGER,
    BBOUND               INTEGER,
    EX                   FLOAT,
    CX                   FLOAT,
    GRAYLEVEL            FLOAT,
constraint PK_IMAGEHBLOCK primary key (IMAGEID, LABEL, IDX)
);

/*==============================================================*/
/* Table: IMAGEHSEG                                             */
/*==============================================================*/
create table IMAGEHSEG
(
    IMAGEID              INTEGER         not null,
    LABEL                INTEGER         not null,
    NBLOCKS              INTEGER         not null,
    NTOTALPIXELS         INTEGER,
    LBOUND               INTEGER,
    TBOUND               INTEGER,
    RBOUND               INTEGER,
    BBOUND               INTEGER,
constraint PK_IMAGEHSEG primary key (IMAGEID, LABEL)
);

/*==============================================================*/
/* Table: IMAGEHSEGINS                                          */
/*==============================================================*/
create table IMAGEHSEGINS
(
    IMAGEID              INTEGER         not null,
    NSEGS                INTEGER         not null,
    LBOUND               INTEGER,
    TBOUND               INTEGER,
    RBOUND               INTEGER,
    BBOUND               INTEGER,
constraint PK_IMAGEHSEGINS primary key (IMAGEID)
);

/*==============================================================*/
/* Table: IMAGES                                                */
/*==============================================================*/
create table IMAGES
(
    ID                   COUNTER         not null,
    TYPE                 INTEGER,
    NAME                 TEXT(255),
    URL                  MEMO,
constraint PK_Image primary key (ID)
);

/*==============================================================*/
/* Index: IDX_IMAGENAME                                         */
/*==============================================================*/
create  index IDX_IMAGENAME on IMAGES
(
   NAME                 ASC
);

/*==============================================================*/
/* Table: IMAGESAFFINITY                                        */
/*==============================================================*/
create table IMAGESAFFINITY
(
    IMAGEID              INTEGER         not null,
    RELATEDIMAGEID       INTEGER         not null,
    MEASURE              FLOAT           not null,
constraint PK_Affinity primary key (IMAGEID, RELATEDIMAGEID)
);

/*==============================================================*/
/* Table: IMAGESINFO                                            */
/*==============================================================*/
create table IMAGESINFO
(
    IMAGEID              INTEGER         not null,
    AUTHOR               TEXT(255),
constraint PK_IMAGESINFO primary key (IMAGEID)
);

/*==============================================================*/
/* Table: IMAGESSEMANTIC                                        */
/*==============================================================*/
create table IMAGESSEMANTIC
(
    IMAGEID              INTEGER         not null,
    SEMANTICID           INTEGER         not null,
constraint PK_IMAGESSEMANTIC primary key (IMAGEID, SEMANTICID)
);

/*==============================================================*/
/* Table: IMAGESSEMANTICWEIGHT                                  */
/*==============================================================*/
create table IMAGESSEMANTICWEIGHT
(
    IMAGEID              INTEGER         not null,
    SEMANTICID           INTEGER         not null,
    WEIGHT               FLOAT           not null,
constraint PK_IMAGESSEMANTICWEIGHT primary key (IMAGEID, SEMANTICID)
);

/*==============================================================*/
/* Table: IMAGESNORMAFFINITY                                     */
/*==============================================================*/
create table IMAGESNORMAFFINITY
(
    IMAGEID              INTEGER         not null,
    RELATEDIMAGEID       INTEGER         not null,
    MEASURE              FLOAT,
constraint PK_NormAff primary key (IMAGEID, RELATEDIMAGEID)
);

/*==============================================================*/
/* Table: IMAGESTYPE                                            */
/*==============================================================*/
create table IMAGESTYPE
(
    ID                   INTEGER         not null,
    DESCRIPTION          TEXT(255),
constraint PK_IMAGESTYPE primary key (ID)
);

/*==============================================================*/
/* Table: SEMANTIC                                              */
/*==============================================================*/
create table SEMANTIC
(
    ID                   COUNTER         not null,
    NAME                 TEXT(255),
    PARENTID             INTEGER,
    IMAGETYPE            INTEGER,
constraint PK_SEMANTIC primary key (ID)
);

/*==============================================================*/
/* Table: SEMANTICINFO                                          */
/*==============================================================*/
create table SEMANTICINFO
(
    SEMANTICID           INTEGER         not null,
    DESCS                TEXT(255),
constraint PK_SEMANTICINFO primary key (SEMANTICID)
);

/*==============================================================*/
/* Table: USERACCESSFREQ                                        */
/*==============================================================*/
create table USERACCESSFREQ
(
    IMAGEID              INTEGER         not null,
    TACCESSED            NUMERIC         not null,
    NACCESSED            INTEGER,
constraint PK_UserFreq primary key (IMAGEID, TACCESSED)
);

/*==============================================================*/
/* Table: USERACCESSPATTERN                                     */
/*==============================================================*/
create table USERACCESSPATTERN
(
    IMAGEID              INTEGER         not null,
    RELATEDIMAGEID       INTEGER         not null,
    TACCESSED            NUMERIC         not null,
    ISACCESSED           INTEGER,
constraint PK_UserPattern primary key (IMAGEID, RELATEDIMAGEID, TACCESSED)
);

alter table HBLOCKMATRIX
   add constraint FK_HMatrix_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table HBLOCKMATRIXINS
   add constraint FK_HMatrixIns_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGE9HSVCLR12TXTFEATURES
   add constraint FK_ClrTxt_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGEHBLOCK
   add constraint FK_HBlock_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGEHSEG
   add constraint FK_HSeg_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGEHSEGINS
   add constraint FK_HSegIns_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGES
   add constraint FK_Images_Type foreign key (TYPE)
      references IMAGESTYPE (ID)
      on update cascade on delete cascade;

alter table IMAGESAFFINITY
   add constraint FK_Affinity_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGESAFFINITY
   add constraint FK_Affinity_Images2 foreign key (RELATEDIMAGEID)
      references IMAGES (ID)

alter table IMAGESINFO
   add constraint FK_Info_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGESSEMANTIC
   add constraint FK_ImagesSemantic_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGESSEMANTIC
   add constraint FK_ImagesSemantic_Semantic foreign key (SEMANTICID)
      references SEMANTIC (ID)
      on update cascade on delete cascade;

alter table IMAGESSEMANTICWEIGHT
   add constraint FK_Weight_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGESSEMANTICWEIGHT
   add constraint FK_Weight_Semantic foreign key (SEMANTICID)
      references SEMANTIC (ID)
      on update cascade on delete cascade;

alter table IMAGESNORMAFFINITY
   add constraint FK_NormAff_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table IMAGESNORMAFFINITY
   add constraint FK_NormAff_Images2 foreign key (RELATEDIMAGEID)
      references IMAGES (ID)

alter table SEMANTIC
   add constraint FK_Semantic_ImagesType foreign key (IMAGETYPE)
      references IMAGESTYPE (ID)

alter table SEMANTIC
   add constraint FK_Semantic_Semantic foreign key (PARENTID)
      references SEMANTIC (ID)

alter table SEMANTICINFO
   add constraint FK_SemanticInfo_Semantic foreign key (SEMANTICID)
      references SEMANTIC (ID)
      on update cascade on delete cascade;

alter table USERACCESSFREQ
   add constraint FK_UserFreq_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table USERACCESSPATTERN
   add constraint FK_UserPattern_Images foreign key (IMAGEID)
      references IMAGES (ID)
      on update cascade on delete cascade;

alter table USERACCESSPATTERN
   add constraint FK_UserPattern_Images2 foreign key (RELATEDIMAGEID)
      references IMAGES (ID)

