#include "molecular_dynamics.h"

void Body::initialize(double x0, double y0, double Vx0, double Vy0, double m0, double R0){
    r.load(x0,y0,0); V.load(Vx0,Vy0,0); m = m0; R = R0;
}

void Body::print(void){
    std::cout<<" , "<<r.x()<<"+"<<R<<"*cos(t),"<<r.y()<<"+"<<R<<"*sin(t)";
}

/**
 * Calculates force between a pair of bodies. 
 * Force between molecules is calculated used Newtonian gravitational force.
 * 
 * @params molecule1, molecule2 : Pair of molecules which force is to be calculated.
 */
void Collider::calculate_force_pair(Body &molecule1, Body &molecule2){
    Vector3D dr, dF;
    dr = molecule2.r - molecule1.r;

    dF = -G*molecule1.m*molecule2.m*vector::unit_vector(dr)/vector::norm2(dr);

    molecule2.add_force(dF); molecule1.add_force((-1.0)*dF);
}

void Collider::calculate_all_forces(Body *molecule){
    for(int i=0; i<N; i++) molecule[i].delete_f();
    
    for(int i=0; i<N; i++)
        for(int j=i+1; j<N; j++)
            calculate_force_pair(molecule[i], molecule[j]);
}

void Collider::move_with_pefrl(Body *molecule, double dt){
    int i;
    for(i=0;i<N;i++) molecule[i].move_r(dt,Zi);
    calculate_all_forces(molecule);
    for(i=0;i<N;i++) molecule[i].move_v(dt,coef1);
    for(i=0;i<N;i++) molecule[i].move_r(dt,Xi);
    calculate_all_forces(molecule);
    for(i=0;i<N;i++) molecule[i].move_v(dt,Lambda);
    for(i=0;i<N;i++) molecule[i].move_r(dt,coef2);
    calculate_all_forces(molecule);
    for(i=0;i<N;i++) molecule[i].move_v(dt,Lambda);
    for(i=0;i<N;i++) molecule[i].move_r(dt,Xi);
    calculate_all_forces(molecule);
    for(i=0;i<N;i++) molecule[i].move_v(dt,coef1);
    for(i=0;i<N;i++) molecule[i].move_r(dt,Zi);
}

double Collider::energy(Body *molecule){
    double E = 0.0;

    // Potential
    for(int i=0; i<N; i++)
        for(int j=i+1; j<N; j++){
            Vector3D dr = molecule[i].r - molecule[j].r;
            E += -G*molecule[j].m/vector::norm(dr);
        }

    // Kinetic
    for(int i=0; i<N; i++)
        E += 0.5*molecule[i].m*vector::norm2(molecule[i].V);

    return E;
}
