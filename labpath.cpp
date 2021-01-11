// '//α' oder '//ω' als Kommentar sind nur fuer die Verwendung dieses Programms als Programmvorlage wichtig
const double& versnr= //α
#include "versdt"
;
#include "kons.h" //α
#include "DB.h" 
#include <tiffio.h>
#define VOMHAUPTCODE // um Funktionsdefinition manchmal mit "__attribute__((weak)) " versehen zu können //ω
#include "labpath.h"
#include "iconvc.h"
// fuer verschiedene Sprachen //α
char const *DPROG_T[T_MAX+1][SprachZahl]=
{
	// T_virtVorgbAllg
	{"virtVorgbAllg()","virtgeneralprefs()"},
	// T_pvirtVorgbSpeziell
	{"pvirtVorgbSpeziell()","pvirtspecialprefs()"},
	// T_virtMusterVorgb
	{"virtMusterVorgb()","virtsampleprefs"},
	// T_pvirtvorrueckfragen
	{"pvirtvorrueckfragen()","pvirtbeforecallbacks()"},
	// T_virtrueckfragen
	{"virtrueckfragen()","virtcallbacks()"},
	//	T_Fehler_beim_Pruefen_von
	{"Fehler beim Pruefen von: ","Error while examining: "},
	// T_Fuege_ein
	{"Fuege ein: ","Inserting: "}, //ω
	// T_eindeutige_Identifikation
	{"eindeutige Identifikation","unique identifier"},
	// T_Laborparameter
	{"Laborparameter","lab parameter"},
	// T_LWert
	{"Wert","value"},
	// T_Einheit
	{"Einheit","unit"},
	// T_Vorwert_1
	{"Vorwert 1","previous value 1"},
	// T_Vorwert_2
	{"Vorwert 2","previous value 2"},
	// T_Normbereich
	{"Normbereich","normal range"},
	// T_Hinweise
	{"Hinweise","hints"},
	// T_Termine
	{"Termine","appointments"},
	// T_Laborwert
	{"(path.) Laborwert","pathol.lab value"},
	// T_pruefdb_k,
	{"pruefdb","checkdb"},
	// T_pruefdb_l,
	{"pruefdb","checkdb"},
	// T_initialisiert_nur_die_Tabellen
	{"initialisiert nur die Tabellen","initializes only the tables"},
	// T_Einlesedatum
	{"Einlesedatum","date of parsing"},
	// T_Pfad,
	{"Pfad","path"},
	// T_Name,
	{"Name","name"},
	// T_Path_Labor_Einlesungen
	{"Pathologische Laborwert-Dateien-Einlesungen","readings of files with pathological lab values"},
	// T_qvz_k,
	{"qvz","sd"},
	// T_qvz_l,
	{"quellvz","sourcedr"},
	// T_Verzeichnis_der_Quelldateien,
	{"Verzeichnis der Quelldateien","directory of the source files"},
	// T_Verzeichnis_der_einzulesenden_Dateien,
	{"Verzeichnis der einzulesenden Dateien","directory of the files to read"},
	// T_prueflpath,
	{"prueflpath()","testlpath()"},
	// T_prueflpatel,
	{"prueflpatel()","testlpatel()"},
	// T_ID_der_Einlesung
	{"ID der Einlesung","id of the reading"},
	// T_fertig
	{"fertig!","finished!"},
	// T_Dateien_gefunden
	{"Dateien gefunden: ","Files found: "},
	{"",""} //α
}; // char const *DPROG_T[T_MAX+1][SprachZahl]=

class TxB Tx((const char* const* const* const*)DPROG_T);
const char *logdt="/var/log/" DPROG "vorgabe.log";//darauf wird in kons.h verwiesen;

using namespace std; //ω
hhcl::hhcl(const int argc, const char *const *const argv):dhcl(argc,argv,DPROG,/*mitcron*/1) //α
{
	//ω
} // hhcl::hhcl //α
// Hier neue Funktionen speichern: //ω
//α
// wird aufgerufen in lauf
void hhcl::virtVorgbAllg()
{
	hLog(violetts+Tx[T_virtVorgbAllg]+schwarz); //ω
	dhcl::virtVorgbAllg(); //α
} // void hhcl::virtVorgbAllg

// wird aufgerufen in lauf
void hhcl::pvirtVorgbSpeziell()
{
	hLog(violetts+Tx[T_pvirtVorgbSpeziell]+schwarz); //ω
	dhcl::pvirtVorgbSpeziell(); //α
	virtMusterVorgb();
} // void hhcl::pvirtVorgbSpeziell

// wird aufgerufen in lauf
void hhcl::virtinitopt()
{ //ω
	opn<<new optcl(/*pptr*/&nurpruefdb,/*art*/puchar,T_pruefdb_k,T_pruefdb_l,/*TxBp*/&Tx,/*Txi*/T_initialisiert_nur_die_Tabellen,/*wi*/0,/*Txi2*/-1,/*rottxt*/string(),/*wert*/1,/*woher*/1);
	opn<<new optcl(/*pname*/"quellvz",/*pptr*/&quellvz,/*art*/pverz,T_qvz_k,T_qvz_l,/*TxBp*/&Tx,/*Txi*/T_Verzeichnis_der_Quelldateien,/*wi*/0,/*Txi2*/-1,/*rottxt*/string(),/*wert*/-1,/*woher*/!quellvz.empty(),Tx[T_Verzeichnis_der_einzulesenden_Dateien]);
	dhcl::virtinitopt(); //α
} // void hhcl::virtinitopt

// wird aufgerufen in lauf
void hhcl::pvirtmacherkl()
{
	erkl<<blau<<Txk[T_Program]<<violett<<DPROG //ω
		<<blau<<" ist etwas ganz Spezielles"<<schwarz; //α
	tabnamen();
} // void hhcl::pvirtmacherkl

void hhcl::prueftbl()
{
	const size_t aktc{0};
	if (!My) initDB();
	prueflpatel(My, aktc, obverb, oblog, /*direkt*/0);
	prueflpath(My, aktc, obverb, oblog, /*direkt*/0);
} // void hhcl::prueftbl

void hhcl::tabnamen()
{
	labpatel="labpatel";
	labpath="labpath";
} // void hhcl::tabnamen

// wird aufgerufen in: prueftbl
void hhcl::prueflpatel(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	hLog(violetts+Tx[T_prueflpatel]+schwarz);
	if (!direkt) {
		Feld felder[] = {
			Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1,0,string(),1),
			Feld("Datum","datetime","0","0",Tx[T_Einlesedatum],0,0,1),
			Feld("Pfad","varchar","100","",Tx[T_Pfad],0,0,1),
			Feld("Name","varchar","100","",Tx[T_Name],0,0,1),
		};
		Feld ifelder1[] = {Feld("Datum")};   Index i1("Datum",ifelder1,elemzahl(ifelder1));
		Feld ifelder2[] = {Feld("Name"),Feld("Pfad")};   Index i2("Pfad",ifelder2,elemzahl(ifelder2));
		Index indices[]={i1,i2};
		Tabelle taba(My,labpatel,felder,elemzahl(felder),indices,elemzahl(indices),0,0,Tx[T_Path_Labor_Einlesungen]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			fLog(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+labpatel,1,1);
			exit(11);
		}
	}
} // prueflpath

// wird aufgerufen in: prueftbl
void hhcl::prueflpath(DB *My, const size_t aktc, const int obverb, const int oblog, const uchar direkt/*=0*/)
{
	hLog(violetts+Tx[T_prueflpath]+schwarz);
	if (!direkt) {
		Feld felder[] = {
			Feld("ID","int","10","",Tx[T_eindeutige_Identifikation],1,1,0,string(),1),
			Feld("elID","int","10","",Tx[T_ID_der_Einlesung],/*obind*/1,/*obauto*/0,/*nnull*/1,/*vdefa*/string(),/*unsig*/1),
		  Feld("Pat_id","int","6","","",0,0,1),
			Feld("Name","varchar","20","",Tx[T_Name],0,0,1),
			Feld("Parameter","varchar","50","",Tx[T_Laborparameter],0,0,1),
			Feld("Wert","varchar","20","",Tx[T_LWert],0,0,1),
			Feld("Einheit","varchar","20","",Tx[T_Einheit],0,0,1),
			Feld("Vorwert_1","varchar","30","",Tx[T_Vorwert_1],0,0,1),
			Feld("Vorwert_2","varchar","30","",Tx[T_Vorwert_2],0,0,1),
			Feld("Normbereich","varchar","300","",Tx[T_Normbereich],0,0,1),
			Feld("Labhinw","varchar","50","Hinweis des Labors",Tx[T_Hinweise],0,0,1),
			Feld("Hinweise","varchar","50","",Tx[T_Hinweise],0,0,1),
			Feld("Termine","varchar","200","",Tx[T_Termine],0,0,1),
		};
		Feld ifelder1[] = {Feld("Pat_id"),Feld("Parameter")}; Index i1("Patid_Par",ifelder1,elemzahl(ifelder1));
		Index indices[]={i1};
		Constraint csts[]{
			Constraint(labpath+labpatel,new Feld{Feld("elID")},1,labpatel,new Feld{Feld("ID")},1,cascade,cascade),
		};
		// auf jeden Fall ginge "binary" statt "utf8" und "" statt "utf8_general_ci"
		Tabelle taba(My,labpath,felder,elemzahl(felder),indices,elemzahl(indices),csts,elemzahl(csts),Tx[T_Laborwert]/*//,"InnoDB","utf8","utf8_general_ci","DYNAMIC"*/);
		if (taba.prueftab(aktc,obverb)) {
			fLog(rots+Tx[T_Fehler_beim_Pruefen_von]+schwarz+labpath,1,1);
			exit(11);
		}
	} // if (!direkt)
} // int pruefouttab(DB *My, string touta, int obverb, int oblog, uchar direkt=0)

// wird aufgerufen in lauf
void hhcl::virtMusterVorgb()
{
	hLog(violetts+Tx[T_virtMusterVorgb]+schwarz); //ω
	dhcl::virtMusterVorgb(); //α
	dbq="quelle";
	quellvz="/DATA/Patientendokumente/SchadeLabor";
} // void hhcl::MusterVorgb

// wird aufgerufen in lauf
void hhcl::pvirtvorzaehler()
{ //ω
} // void hhcl::virtvorzaehler() //α
//ω

// wird aufgerufen in lauf
void hhcl::virtzeigversion(const string& ltiffv/*=nix*/)
{
	dhcl::virtzeigversion(ltiffv); //α
} // void hhcl::virtzeigversion

// wird aufgerufen in lauf
void hhcl::pvirtvorrueckfragen()
{
	hLog(violetts+Tx[T_pvirtvorrueckfragen]+schwarz);
	if (rzf) { //ω
	}
	//α
} // void hhcl::pvirtvorrueckfragen

// wird aufgerufen in lauf
void hhcl::virtpruefweiteres()
{ //ω
	hcl::virtpruefweiteres(); // z.Zt. leer //α
} // void hhcl::virtpruefweiteres

// wird aufgerufen in lauf
void hhcl::virtzeigueberschrift()
{ //ω
	// hier ggf. noch etwas an 'uebers' anhaengen //α
	uebers<<" (Einlesung pathologischer Laborwerte) ";
	hcl::virtzeigueberschrift();
} // void hhcl::virtzeigueberschrift

void hhcl::pvirtnachrueckfragen()
{
} // void hhcl::pvirtnachrueckfragen


bool getasciiline(mdatei& mdat,string& zeile)
{
	string zwi;
	bool erg{0};
	static iconvc i("ISO-8859-1","UTF-8//TRANSLIT");
  if (getline(mdat,zwi)) {
		if (zwi.length()) {
			zeile=i.convert(zwi);
			erg=true; 
		}
	}
	if (!erg) zeile.clear();
	return erg;
} // getasciiline

#ifdef false
string ausg(string str)
{
	string erg;
	iconvc i("ISO-8859-1","UTF-8//TRANSLIT");
	return i.convert(str);
    char *q=(char*)str.c_str();
		char *dest = new char[2*str.length()];
    size_t outbytes = sizeof dest;
    size_t inbytes = strlen(q);
    iconv_t conv = iconv_open("UTF-8//TRANSLIT", "ISO-8859-1");
    if (conv == (iconv_t)-1) {
        return str;
//        perror("iconv_open");
    }
    if (iconv(conv, &q, &inbytes, &dest, &outbytes) == (size_t)-1) {
        return str;
//        perror("iconv");
    }
    dest[sizeof dest- outbytes] = 0;
    return string(dest);
		string ret{dest};
		delete dest;
		return ret;
}
#endif

// wird aufgerufen in lauf
void hhcl::pvirtfuehraus()
{ //ω
	auto altZDB{ZDB};
	string datid;
	int geprueft{0};
	//	ZDB=1;
	const size_t aktc{0};
	// unsigned long verarbeitet{0};
	if (rzf) tabnamen(); // nach rueckfragen
	if (nurpruefdb) {
		prueftbl();
	} else {
		pruefverz(quellvz,obverb,oblog);
		svec lrue;
		systemrueck("find "+quellvz+" -maxdepth 1 -type f -iname '*.csv' -printf '%TY%Tm%Td%TH%TM%TS\t%p\n' "+string(obverb?"":"2>/dev/null")+"|sort|cut -f2", obverb,oblog,&lrue,/*obsudc=*/0);
		fLog(blaus+Tx[T_Dateien_gefunden]+schwarz+ltoan(lrue.size()),1,oblog);
		if (lrue.size()) {
			prueftbl();
		}
		svec eindfeld; eindfeld<<"id";
		for(size_t i=0;i<lrue.size();i++) {
			string *aktl{&lrue[i]};
			RS nachschau(My,"SELECT Datum FROM `"+labpatel+"` WHERE name="+sqlft(My->DBS,base_name(*aktl)),aktc,ZDB);
			if (!nachschau.obqueryfehler) {
				char ***cerg{0};
				if (!(cerg=nachschau.HolZeile())||!*cerg) {
					if (!geprueft) {
						prueftbl();
						geprueft=1;
					}
					insv reing(My,/*itab*/labpatel,aktc,/*eindeutig*/0,eindfeld,/*asy*/0,/*csets*/0);
					/*auto*/chrono::system_clock::time_point jetzt=chrono::system_clock::now();
					reing.hz("Name",base_name(*aktl));
					reing.hz("Pfad",dir_name(*aktl));
					reing.hz("Datum",&jetzt);
					reing.schreib(/*sammeln*/0,/*obverb*/obverb,/*idp*/&datid);

					mdatei mdat(*aktl,ios::in);
					string zeile;
					if (mdat.is_open()) {
						uchar obanf{0};
						string erstl;
						string umw;
						while(getasciiline(mdat,zeile)) {
//							umw=ausg(zeile);
							caus<<rot<<zeile<<schwarz<<endl;
							caus<<rot<<umw<<schwarz<<endl;
							char innen{0}, ch;
							svec erg;
							size_t i{0};
							erg<<"";
							while (1) {
								for(size_t i=0;i<zeile.length();i++) {
									ch=zeile[i];
									if (ch==10 || ch==13) {
										if (innen) erg[erg.size()-1]+='|'; 
									} else if (!innen && ch==',') {
										erg<<"";
									} else if (ch=='"') {
										innen=!innen;
									} else {
										erg[erg.size()-1]+=ch; 
										// caus<<gruen<<"ch: "<<ch<<" erg.size(): "<<erg.size()<<" erg.size()-1: "<<erg.size()-1<<" erg[erg.size()-1]: "<<erg[erg.size()-1]<<schwarz<<" innen: "<<(int)innen<<endl;
									}
								}
								if (!innen) break;
								if (!getasciiline(mdat,zeile)) break;
//								umw=ausg(zeile);
								caus<<"i: "<<i<<" "<<rot<<zeile<<schwarz<<endl;
							}
							for(size_t i=0;i<erg.size();i++) {
								if (erg[i]!="")
								caus<<"i: "<<i<<" "<<blau<<erg[i]<<schwarz<<endl;
							}
							insv reine(My,/*itab*/labpath,aktc,/*eindeutig*/0,eindfeld,/*asy*/0,/*csets*/0);
							svec nteile;
							aufSplit(&nteile, erg[0]);
							if (!obanf) {
								if (erg[0].find("Erstellt")!=string::npos) {
									erstl=nteile[nteile.size()-1];
									obanf=1;
								}
							} else if (obanf==1) {
								if (erg[0].find("Patient")!=string::npos) {
									obanf=2;
								}
							} else {
								uchar obname{0},obpid{0};
								string pid,gschl,abkue,einh;
								RS pd(My,"SELECT COUNT(1) OVER() zl, f.pat_id, CONCAT(gesname(f.pat_id),' (',patalter(f.pat_id),')'),geschlecht FROM faelle f LEFT JOIN namen n USING (pat_id) WHERE n.nachname='"+nteile[nteile.size()-1]+"' AND n.vorname LIKE '"+nteile[0]+"%' AND BhFB<STR_TO_DATE('"+erstl+"','%d.%m.%Y') AND (BhFE1>ADDDATE(STR_TO_DATE('"+erstl+"','%d.%m.%Y'),-4) OR BhFE1=18991230) GROUP BY f.pat_id;",aktc,ZDB);
								if (!pd.obqueryfehler) {
									char ***cerg{0};
									while (cerg=pd.HolZeile(),cerg?*cerg:0) {
										if (!strcmp(cjj(cerg,0),"1")) {
											pid=cjj(cerg,1);
											reine.hz("Pat_id",cjj(cerg,1));
											obpid=1;
											if (cerg[2]) {
												reine.hz("Name",cjj(cerg,2));
												obname=1;
											}
											if (cerg[3]) gschl=cjj(cerg,3);
										} else if (strcmp(cjj(cerg,0),"0")) { // mehrere Patienten gefunden
											RS npid(My,"SELECT COUNT(1) OVER() zl, f.pat_id, CONCAT(gesname(f.pat_id),' (',patalter(f.pat_id),')'),geschlecht "
													"FROM labor2a l LEFT JOIN namen n USING(pat_id)"
													"WHERE l.pat_id IN (SELECT GROUP_CONCAT(pat_id SEPARATOR ',') FROM namen WHERE TRIM(CONCAT(titel,' ',vorname,' ',nvors, if(nvors='','',' '),nachname)) = '"+nteile[nteile.size()-1]+"')"
													"AND zeitpunkt BETWEEEN DATE_SUB(STR_TO_DATE('"+erstl+"','%d.%m.%Y'),INTERVAL 7 DAY) AND DATE_ADD(STR_TO_DATE('"+erstl+"','%d.%m.%Y'),INTERVAL 1 DAY) ORDER BY zeitpunkt DESC",aktc,ZDB); 
											if (!npid.obqueryfehler) {
												char ***cerg{0};
												while (cerg=npid.HolZeile(),cerg?*cerg:0) {
													if (!strcmp(cjj(cerg,0),"1")) {
														pid=cjj(cerg,1);
														reine.hz("Pat_id",cjj(cerg,1));
														obpid=1;
														if (cerg[2]) {
															reine.hz("Name",cjj(cerg,2));
															obname=1;
														}
														if (cerg[3]) gschl=cjj(cerg,3);
													} // 													if (!strcmp(cjj(cerg,0),"1"))
													break;
												} // 												while (cerg=npid.HolZeile(),cerg?*cerg:0)
											} // if (!npid.obqueryfehler)
										} // if (!strcmp(cjj(cerg,0),"1")) ... else if (strcmp(cjj(cerg,0),"0"))
										break;
									} // 									while (cerg=pd.HolZeile(),cerg?*cerg:0)
									if (!obname)
										reine.hz("Name",erg[0]);
									reine.hz("elID",datid);
									size_t p1,p2,p3,p4;
									uchar pl{3},oblh{0};
									if ((p1=erg[1].find(':'))!=string::npos) {
										abkue=erg[1].substr(0,p1);
										reine.hz("Parameter",abkue);
										if ((p2=erg[1].find(' ',p1))!=string::npos) {
											reine.hz("Wert",erg[1].substr(p1+1,p2-p1-1));
											if ((p3=erg[1].find('(',p2))!=string::npos) {
												einh=erg[1].substr(p2+1,p3-p2-2);
												reine.hz("Einheit",einh);
													p4=erg[1].find("|",p3);
													if (p4!=string::npos) {
														reine.hz("Normbereich",erg[1].substr(p3+1,p4-p3-1));
														p3=p4;
														oblh=1;
													}
												p4=erg[1].find(" / ",p3);
												if (p4==string::npos) {
													p4=erg[1].find(")",p3);
													pl=1;
												}
												if (p4!=string::npos) {
													reine.hz(oblh?"Labhinw":"Normbereich",erg[1].substr(p3+(oblh?1:pl),p4-p3-(oblh?pl:1)));
												}
												if (!oblh)
													reine.hz("Labhinw","");
											}
										}
									} // 									if ((p1=erg[1].find(':'))!=string::npos)
									if (obpid) {
										RS tm(My,"SELECT TRIM(GROUP_CONCAT(CONCAT(DATE_FORMAT(zp,'%d.%m.%y'),' ',LEFT(raum,3)) ORDER BY zp SEPARATOR '  ')) term FROM termine t WHERE zp >= date(now()) AND pid = "+pid,aktc,ZDB);
										if (!tm.obqueryfehler) {
											char ***cerg{0};
											while (cerg=tm.HolZeile(),cerg?*cerg:0) {
												reine.hz("Termine",cjj(cerg,0));
												break;
											}
										}

										RS llb(My,"CALL geslabdp("+pid+",\"WHERE abkü='"+abkue+"' AND einheit='"+einh+"' "
												      "AND zeitpunkt<=SUBDATE(STR_TO_DATE('"+erstl+"','%d.%m.%Y'),1) GROUP BY zeitpunkt DESC LIMIT 2\")",aktc,2);
										if (!llb.obqueryfehler) {
											char ***cerg{0};
											cerg=llb.HolZeile(); if (cerg?*cerg:0) reine.hz("Vorwert_1",cjj(cerg,0));
											cerg=llb.HolZeile(); if (cerg?*cerg:0) reine.hz("Vorwert_2",cjj(cerg,0));
										}
									}
									reine.schreib(/*sammeln*/0,/*obverb*/obverb,/*idp*/0);
								} // 								if (!pd.obqueryfehler)
							}
						}
					}
				}
			}
		}
	} // 		else if (!loeschalle && !loeschunvollst && umben.empty())
	fLog(blaus+Tx[T_fertig]+schwarz,1,oblog);
	ZDB=altZDB;
} // void hhcl::pvirtfuehraus  //α

// wird aufgerufen in lauf
void hhcl::virtschlussanzeige()
{   //ω
	dhcl::virtschlussanzeige(); //α
} // void hhcl::virtschlussanzeige

// wird aufgerufen in: main
void hhcl::virtautokonfschreib()
{
	// int altobverb=obverb;
	// obverb=1;
	hLog(violetts+Txk[T_autokonfschreib]+schwarz+", "+Txk[T_zu_schreiben]+((rzf||hccd.obzuschreib)?Txk[T_ja]:Txk[T_nein]));
	/*//
		capizukonf und hylazukonf hier immer 0
		char buf[200];
		sprintf(buf,"rzf: %d, capizukonf: %d, hylazukonf: %d, obkschreib: %d",(int)rzf, (int)capizukonf, (int)hylazukonf, (int)obkschreib);
		hLog(blaus+buf+schwarz);
	 */
	struct stat kstat={0};
	if (lstat(akonfdt.c_str(),&kstat))
		hccd.obzuschreib=1;
	if (rzf||hccd.obzuschreib) {
		hLog(gruens+Tx[T_schreibe_Konfiguration]+schwarz,/*oberr*/obverb);
		// restliche Erklaerungen festlegen
		////    agcnfA.setzbem("language",sprachstr);
		hcl::virtautokonfschreib(); //ω
	} // if (rzf||obkschreib) //α
	// obverb=altobverb;
} // void hhcl::virtautokonfschreib

hhcl::~hhcl() 
{ //ω
} //α

void hhcl::virtlieskonfein()
{
	const int altobverb{obverb};
	//	obverb=1;
	hLog(violetts+Txk[T_virtlieskonfein]+schwarz);
	//nachclvors=vorsl;
	hcl::virtlieskonfein(); //ω
	hLog(violetts+Txk[T_Ende]+Txk[T_virtlieskonfein]+schwarz); //α
	obverb=altobverb;
} // void hhcl::virtlieskonfein()

int main(int argc,char** argv)
{
	if (argc>1) { //ω
	} //α
	hhcl hhi(argc,argv); // hiesige Hauptinstanz, mit lngzuw, setzlog und pruefplatte
	hhi.lauf(); // Einleitungsteil mit virtuellen Funktionen, 
	// mit virtVorgbAllg,pvirtVorgbSpeziell,initopt,parsecl,pvirtmacherkl,zeighilfe,virtlieskonfein,verarbeitkonf,lieszaehlerein,MusterVorgb,dovi,dovs,virtzeigversion
	// virtautokonfschreib,update,
	return hhi.retu;
} // int main 

void hhcl::virttesterg()
{
} //ω
