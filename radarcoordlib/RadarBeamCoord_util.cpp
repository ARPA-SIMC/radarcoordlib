#include <iostream>
#include <radarcoordlib/RadarBeamCoord_util.hpp>
    RadarBeamCoord_util::RadarBeamCoord_util(float ea){ setEarthRadius(ea);}
    void RadarBeamCoord_util::setEarthRadius (float ea) { EarthRadius = ea; }
    float RadarBeamCoord_util::getEarthRadius () { return EarthRadius; }

// compute beamHeight from elevation and surface distance - Doviak Zrnic, pg 13 eq 2.28a
    float RadarBeamCoord_util::elev_sd_2_beamHeight(float elev, float surf_dist){
	float h;
	float kea;
	kea=KeA(EarthRadius);
	if (surf_dist <0) throw 20;
	h = kea * (cos(DEG2RAD(elev))/cos(DEG2RAD(elev)+surf_dist/kea) -1.);
	return h;
    }
// compute beamHeight from elevation and surface distancev - Doviak Zrnic, pg 13 eq 2.28a
    float RadarBeamCoord_util::elev_sd_2_beamHeight(float elev, float surf_dist,float alt_rad){
	float h;
	h = alt_rad + RadarBeamCoord_util::elev_sd_2_beamHeight(elev,surf_dist);
	return h;
}

// compute beamHeight from elevation and beam range distance - Doviak Zrnic, pg 13 eq 2.28b
    float RadarBeamCoord_util::elev_br_2_beamHeight(float elev, float  beam_range){
	float h;
	float kea;
	kea=KeA(EarthRadius);
	if (beam_range <0) throw 20;
	h=sqrt(pow(beam_range,2.)+pow(kea,2.)+2*kea*beam_range*sin(DEG2RAD(elev)))-kea;
	return h;
}
// compute beamHeight from elevation and beam range distance - Doviak Zrnic, pg 13 eq 2.28b
    float RadarBeamCoord_util::elev_br_2_beamHeight(float elev, float beam_range, float alt_rad){
	float h;
	h = alt_rad + RadarBeamCoord_util::elev_br_2_beamHeight(elev,beam_range);
	return h;
}

// compute surfaceDistance from gate radar coordinates - Doviak Zrnic, pg 13 eq 2.28c
    float RadarBeamCoord_util::elev_br_bh_2_surfDistance    (float elev, float beam_range, float beam_height){
	float d;
	float kea;
	kea=KeA(EarthRadius);
	d=kea*asin(beam_range*cos(DEG2RAD(elev))/(kea+beam_height));
	return d;
}
// compute surfaceDistance from gate radar coordinates - Doviak Zrnic, pg 13 eq 2.28c
    float RadarBeamCoord_util::elev_br_bh_2_surfDistance    (float elev, float beam_range, float beam_height,float alt_rad){
       float d;
	d=RadarBeamCoord_util::elev_br_bh_2_surfDistance    (elev, beam_range, beam_height-alt_rad);
	return d;
}

// compute surfaceDistance from gate range and elevation - Doviak Zrnic, pg 13 eq (2.28b + 2.28c)
    float RadarBeamCoord_util::elev_br_2_surfDistance    (float elev, float beam_range){
	float h,d;
	float kea;
	h=RadarBeamCoord_util::elev_br_2_beamHeight(elev,beam_range);
	d=RadarBeamCoord_util::elev_br_bh_2_surfDistance(elev,beam_range,h);
	return d;
}

// compute beam range distance from elevation, surface distance and beam height - Doviak Zrnic, pg 13 eq (invertita) 2.28c
    float RadarBeamCoord_util::elev_sd_bh_2_beamRange(float elev, float surfDistance, float beam_height){
	float r;
	float kea;
	kea=KeA(EarthRadius);
	if (surfDistance < 0 ) throw 20;
	r=(kea+beam_height)*sin(surfDistance/kea)/cos(DEG2RAD(elev));
	return r;
}
// compute beam range distance from elevation, surface distance and beam height - Doviak Zrnic, pg 13 eq (invertita) 2.28c
    float RadarBeamCoord_util::elev_sd_bh_2_beamRange(float elev, float surfDistance, float beam_height,float alt_rad){
    	float r;
	r= RadarBeamCoord_util::elev_sd_bh_2_beamRange(elev, surfDistance, beam_height-alt_rad);
	return r;
}

// compute beamRange  from elevation and surface distance
    float RadarBeamCoord_util::elev_sd_2_beamRange(float elev, float surfDistance) {
	float r, h;
	if ( surfDistance < 0 ) throw 20;
	h = RadarBeamCoord_util::elev_sd_2_beamHeight(elev, surfDistance);
	r = RadarBeamCoord_util::elev_sd_bh_2_beamRange(elev, surfDistance, h);
	return r;
}
// compute beam elevation from beam height and beam range
    float RadarBeamCoord_util::br_bh_2_elev(float beamRange, float beamHeight){
	float elev, elev_inc;
	float h, h1;
//	if (beamHeight < 0. || beamHeight > beamRange ) throw 20;
	if ( beamHeight > beamRange ) return 90.;
	elev=-2.;							//valore iniziale di ricerca elevazione
	h1=RadarBeamCoord_util::elev_br_2_beamHeight(elev,beamRange);    	// valore iniziale elevazione
	if (beamHeight - h1 > 0) {
	  elev_inc = 1.; 					// valore iniziale incremento elevazione
	} else if ( beamHeight-h1 < 0 && beamHeight - h1 + 100.> 0) {
	  elev_inc = 0.0001;					// siamo già all'altezza giusta 
	} else throw 20;
// search nearest elevation to given bin-range and bin-height
	while (elev_inc >0.001){ 
     		elev=elev + elev_inc;
	   h=RadarBeamCoord_util::elev_br_2_beamHeight(elev,beamRange);    	
	   if ( (h1-beamHeight)*(h-beamHeight) > 0) {
	     h1=h;
	   } else {
	     elev = elev-elev_inc;
	     elev_inc=elev_inc * 0.1;
	   }
	}
	return elev;
}
// compute beam elevation from beam height and beam range
    float RadarBeamCoord_util::br_bh_2_elev(float beamRange, float beamHeight,float alt_rad){
    	float elev;
	if (beamHeight < 0.) throw 20;
	elev=RadarBeamCoord_util::br_bh_2_elev(beamRange, beamHeight-alt_rad);
	return elev;
}

// compute beamRange  from elevation and surface distance
    float RadarBeamCoord_util::ds_bh_2_elev(float surfDistance, float beamHeight){
	float elev, elev_inc;
	float h, h1;
//	if (beamHeight < 0. ) throw 20;
	elev=-2.;							//valore iniziale di ricerca elevazione
	h1=RadarBeamCoord_util::elev_sd_2_beamHeight(elev,surfDistance);    	// valore iniziale elevazione
	if (beamHeight - h1 > 0) {
	  elev_inc = 1.; 					// valore iniziale incremento elevazione
	} else if ( beamHeight-h1 < 0 && beamHeight - h1 + 100.> 0) {
	  elev_inc = 0.0001;					// siamo già all'altezza giusta 
	} else throw 20;
// search nearest elevation to given bin-range and bin-height
	while (elev_inc >0.001 && elev < 90.){ 
	   elev=elev + elev_inc;
	   h=RadarBeamCoord_util::elev_sd_2_beamHeight(elev,surfDistance);    	
	   if ( (h1-beamHeight)*(h-beamHeight) > 0) {
	     h1=h;
	   } else {
	     elev = elev-elev_inc;
	     elev_inc=elev_inc * 0.1;
	   }
	   if(elev >= 90.)elev=90.;
	}
	return elev;
}
// compute beamRange  from elevation and surface distance
    float RadarBeamCoord_util::ds_bh_2_elev(float surfDistance, float beamHeight,float alt_rad){
	if (beamHeight < 0.) throw 20;
     return RadarBeamCoord_util::ds_bh_2_elev(surfDistance, beamHeight-alt_rad);
}
