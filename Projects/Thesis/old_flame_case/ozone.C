//-----------------------------------------------------------------------bl-
//--------------------------------------------------------------------------
//
// GRINS - General Reacting Incompressible Navier-Stokes
//
// Copyright (C) 2014-2015 Paul T. Bauman, Roy H. Stogner
// Copyright (C) 2010-2013 The PECOS Development Team
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the Version 2.1 GNU Lesser General
// Public License as published by the Free Software Foundation.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc. 51 Franklin Street, Fifth Floor,
// Boston, MA  02110-1301  USA
//
//-----------------------------------------------------------------------el-

#include "grins_config.h"

#include <iostream>
#include <math.h>
// GRINS
#include "grins/simulation.h"
#include "grins/simulation_builder.h"
#include "grins/physics_factory.h"
#include "grins/bc_factory.h"
#include "grins/physics_factory.h"

// libMesh
#include "libmesh/getpot.h"

// Function for getting initial temperature field
libMesh::Real initial_values( const libMesh::Point& p, const libMesh::Parameters &params,
		     const std::string& system_name, const std::string& unknown_name );

int main(int argc, char* argv[])
{
  // Check command line count.
  if( argc < 2 )
    {
      // TODO: Need more consistent error handling.
      std::cerr << "Error: Must specify libMesh input file." << std::endl;
      exit(1); // TODO: something more sophisticated for parallel runs?
    }

  // libMesh input file should be first argument
  std::string libMesh_input_filename = argv[1];

  // Create our GetPot object.
  GetPot libMesh_inputfile( libMesh_input_filename );

#ifdef GRINS_USE_GRVY_TIMERS
  grvy_timer.BeginTimer("Initialize Solver");
#endif

  // Initialize libMesh library.
  libMesh::LibMeshInit libmesh_init(argc, argv);

  GRINS::SimulationBuilder sim_builder;

  GRINS::Simulation grins( libMesh_inputfile,
			   sim_builder,
                           libmesh_init.comm() );

  //FIXME: We need to move this to within the Simulation object somehow...
  std::string restart_file = libMesh_inputfile( "restart-options/restart_file", "none" );

  // If we are "cold starting", setup the flow field.
  if( restart_file == "none" )
    {
      // Asssign initial temperature value
      std::string system_name = libMesh_inputfile( "screen-options/system_name", "GRINS" );
      std::tr1::shared_ptr<libMesh::EquationSystems> es = grins.get_equation_system();
      const libMesh::System& system = es->get_system(system_name);

      libMesh::Real dummy = libMesh_inputfile( "Physics/ReactingLowMachNavierStokes/peak_T", 0.0 );
      libMesh::Parameters &params = es->parameters;

      libMesh::Real& peak_T = params.set<libMesh::Real>("Peak_T");
      peak_T = dummy;

      std::cout << "==============================================" << std::endl;
      std::cout << "Projecting Solution." << std::endl;
      std::cout << "==============================================" << std::endl;
      system.project_solution( initial_values, NULL, params );
      std::cout << "==============================================" << std::endl;
      std::cout << "Done Projecting Solution!" << std::endl;
      std::cout << "==============================================" << std::endl;
    }


  grins.run();

  return 0;
}

libMesh::Real initial_values( const libMesh::Point& p, const libMesh::Parameters & params,
                              const std::string& , const std::string& unknown_name )
{
  libMesh::Real value = 0.0;

  libMesh::Real x = p(0);
  libMesh::Real y = p(1);

 // const libMesh::Real& peak_T = params.get<libMesh::Real>("Peak_T");

  if( unknown_name == "T" )
   {
   	  double T0 = 300;
      double T1 = 900;
      //value = 1.5*1.25*1.14285*1.167*2*1.3636*1.1*1.1*0.0405077*10*48000.0*(y*(0.005-y));
      if (x <= 0.004)
      {
      value = T0;
      }
      else if(x >0.004 && x<= 0.006)
      {
      double t = double(x - 0.004)/double(0.006 - 0.004);
      value = T0*((2*pow(t,3) - 3*pow(t,2) + 1)) + T1*((-2*pow(t,3) + 3*pow(t,2)));
      }
      else if(x >0.006 )
      {
      value = T1;
      }
    }
  else if( unknown_name == "w_O3" )
   {
      //value = 1.5*1.25*1.14285*1.167*2*1.3636*1.1*1.1*0.0405077*10*48000.0*(y*(0.005-y));
    	double w1_0 = 0.2;
      double w1_1 = 0.0;
      //value = 1.5*1.25*1.14285*1.167*2*1.3636*1.1*1.1*0.0405077*10*48000.0*(y*(0.005-y));
      if (x <= 0.004)
      {
      value = w1_0;
      }
      else if(x >0.004 && x<= 0.006)
      {
      double t = double(x - 0.004)/double(0.006 - 0.004);
      value = w1_0*((2*pow(t,3) - 3*pow(t,2) + 1)) + w1_1*((-2*pow(t,3) + 3*pow(t,2)));
      }
      else if(x >0.006 )
      {
      value = w1_1;
      }
    }
  else if( unknown_name == "w_O2" )
    {
    	double w_0 = 0.8;
      double w_1 = 1.0;
      //value = 1.5*1.25*1.14285*1.167*2*1.3636*1.1*1.1*0.0405077*10*48000.0*(y*(0.005-y));
      if (x <= 0.004)
      {
      value = w_0;
      }
      else if(x >0.004 && x<= 0.006)
      {
      double t = double(x - 0.004)/double(0.006 - 0.004);
      value = w_0*((2*pow(t,3) - 3*pow(t,2) + 1)) + w_1*((-2*pow(t,3) + 3*pow(t,2)));
      }
      else if(x >0.006 )
      {
      value = w_1;
      }
    }
  else if( unknown_name == "u")
    {
      double u_0 = 0.3;
      double u_1 = 0.8;
      double v ; 
      if(y <= 1.1)
      {
      v = 1*(1-(pow(y,2)/pow(1.1,2)));
      }
      else if (y > 1.1 && y < 1.3  )
      {
      v = 0.0;
      }
      else if
      {
      v = 1*(1-(pow(y-1.95,2)/pow(0.65,2)));
      }
     // double v = 1000*(y*(0.005-y))/0.0025/2.5;
      
      if (x <= 0.003)
      {
      value = v*u_0;
      }
      else if(x >0.003 && x<= 0.007)
      {
      double t = double(x - 0.003)/double(0.007 - 0.003);
      value = v*(u_0*((2*pow(t,3) - 3*pow(t,2) + 1)) + u_1*((-2*pow(t,3) + 3*pow(t,2))));
      }
      else if(x >0.007 )
      {
      value = v*u_1;
      }
      
      
    }

  return value;
}
