[Mesh]
  [generator]
    type = GeneratedMeshGenerator
    dim = 2
    xmax = 80
    ymax = 80
    nx = 80
    ny = 80
  []
  [subdomain1]
    type = SubdomainBoundingBoxGenerator
    input = generator
    bottom_left = '0 0 0'
    top_right = '24 24 0'
    block_id = 3
  []
  [subdomain2]
    type = SubdomainBoundingBoxGenerator
    input = subdomain1
    bottom_left = '24 0 0'
    top_right = '56 24 0'
    block_id = 2
  []
  [subdomain3]
    type = SubdomainBoundingBoxGenerator
    input = subdomain2
    bottom_left = '0 24 0'
    top_right = '24 56 0'
    block_id = 2
  []
  [subdomain4]
    type = SubdomainBoundingBoxGenerator
    input = subdomain3
    bottom_left = '24 24 0'
    top_right = '56 56 0'
    block_id = 1
  []
  [subdomain5]
    type = SubdomainBoundingBoxGenerator
    input = subdomain4
    bottom_left = '56 0 0'
    top_right = '80 80 0'
    block_id = 3
  []
  [subdomain6]
    type = SubdomainBoundingBoxGenerator
    input = subdomain5
    bottom_left = '0 56 0'
    top_right = '56 80 0'
    block_id = 3
  []
[]

[Variables]
    [flux_group1]
        order = FIRST
        family = LAGRANGE
    []

    [flux_group2]
        order = FIRST
        family = LAGRANGE
    []

    [delayed_c1]
        order = FIRST
        family = LAGRANGE
    []
[]

[AuxVariables]
    [delayed_nucleus]
        order = CONSTANT
        family = MONOMIAL
    []

    [fission]
        order = CONSTANT
        family = MONOMIAL
    []
[]

[Functions]
    [absorptionCrossSection_group2]
        type = Transientproblem2_AbsorptionCrossSection_group2
    []
[]

[Kernels]
    [timederivative_group1]
        type = NeutronTimeDerivative_group1
        variable = flux_group1
    []

    [diffusion_group1]
        type = Diffusion_term_Twogroups_group1
        variable = flux_group1
    []

    [fission_group1]
        type = Fission_Twogroups_Transientproblem_group1
        variable = flux_group1
        coefficient = -1.0
        keff = 0.91321
        otherflux_1 = flux_group2
    []

    [absorption_group1]
        type = Absorption_Twogroups_group1
        variable = flux_group1
    []

    [scattering_group1]
        type = Scattering_Twogroups_group1
        variable = flux_group1
        otherflux_1 = flux_group2
    []

    [delayedneutronsources_group1]
        type = Delayed_NeutronSources_group1
        variable = flux_group1
        delayed_nucleus = delayed_nucleus
    []

    
    [timederivative_group2]
        type = NeutronTimeDerivative_group2
        variable = flux_group2
    []

    [diffusion_group2]
        type = Diffusion_term_Twogroups_group2
        variable = flux_group2
    []

    [fission_group2]
        type = Fission_Twogroups_Transientproblem_group2
        variable = flux_group2
        coefficient = -1.0
        keff = 0.91321
        otherflux_1 = flux_group1
    []

    [absorption_group2]
        type = Absorption_Twogroups_group2
        variable = flux_group2
    []

    [scattering_group2]
        type = Scattering_Twogroups_group2
        variable = flux_group2
        otherflux_1 = flux_group1
    []

    [delayedneutronsources_group2]
        type = Delayed_NeutronSources_group2
        variable = flux_group2
        delayed_nucleus = delayed_nucleus
    []


    [delayed_nucleus_c1_timederivate]
        type = DelayedNeutron_TimeDerivate
        variable = delayed_c1
    []

    [delayed_nucleus_c1_decayandfission]
        type = DelayedNeutron_Decayandfission
        variable = delayed_c1
        num = 1
        keff = 0.91321
        flux_group1 = flux_group1
        flux_group2 = flux_group2
        fission = fission
    []
[]

[AuxKernels]
    [delayednucleus_one]
        type = DelayedNucleus_one
        variable = delayed_nucleus
        delayed_nucleus_1 = delayed_c1
    []

    [fission_aux]
        type = Fission_aux
        variable = fission
        flux_group1 = flux_group1
        flux_group2 = flux_group2
        execute_on = 'initial timestep_end'
    []
[]

[Materials]
    [materail_1]
        type = Material_TWIGL_Twogroups_forTransientproblem2ofTWIGL
        block = '1'
        diffusion_coefficient_group1 = 1.4
        diffusion_coefficient_group2 = 0.4
        absorption_cross_section_group1 = 0.01
        # absorption_cross_section_group2 = 0.1465 # Changed!
        scattering_cross_section_group1to2 = 0.01
        scattering_cross_section_group2to1 = 0
        kai_group1 = 1
        kai_group2 = 0
        fission_cross_section_v_group1 = 0.007
        fission_cross_section_v_group2 = 0.2
        velocity_group1 = 10000000
        velocity_group2 = 200000
        beta = 0.0075
        beta_1 = 0.0075
        beta_2 = 0.0
        beta_3 = 0.0
        beta_4 = 0.0
        beta_5 = 0.0
        beta_6 = 0.0
        lambda_1 = 0.08
        lambda_2 = 0.0
        lambda_3 = 0.0
        lambda_4 = 0.0
        lambda_5 = 0.0
        lambda_6 = 0.0
    []

    [material_1_absorption]
        type = GenericFunctionMaterial
        block = '1'
        prop_names = absorption_cross_section_group2
        prop_values = absorptionCrossSection_group2
    [../]

    [materail_2]
        type = Material_TWIGL_Twogroups
        block = '2'
        diffusion_coefficient_group1 = 1.4
        diffusion_coefficient_group2 = 0.4
        absorption_cross_section_group1 = 0.01
        absorption_cross_section_group2 = 0.15
        scattering_cross_section_group1to2 = 0.01
        scattering_cross_section_group2to1 = 0
        kai_group1 = 1
        kai_group2 = 0
        fission_cross_section_v_group1 = 0.007
        fission_cross_section_v_group2 = 0.2
        velocity_group1 = 10000000
        velocity_group2 = 200000
        beta = 0.0075
        beta_1 = 0.0075
        beta_2 = 0.0
        beta_3 = 0.0
        beta_4 = 0.0
        beta_5 = 0.0
        beta_6 = 0.0
        lambda_1 = 0.08
        lambda_2 = 0.0
        lambda_3 = 0.0
        lambda_4 = 0.0
        lambda_5 = 0.0
        lambda_6 = 0.0
    []

    [materail_3]
        type = Material_TWIGL_Twogroups
        block = '3'
        diffusion_coefficient_group1 = 1.3
        diffusion_coefficient_group2 = 0.5
        absorption_cross_section_group1 = 0.008
        absorption_cross_section_group2 = 0.05
        scattering_cross_section_group1to2 = 0.01
        scattering_cross_section_group2to1 = 0
        kai_group1 = 1
        kai_group2 = 0
        fission_cross_section_v_group1 = 0.003
        fission_cross_section_v_group2 = 0.06
        velocity_group1 = 10000000
        velocity_group2 = 200000
        beta = 0.0075
        beta_1 = 0.0075
        beta_2 = 0.0
        beta_3 = 0.0
        beta_4 = 0.0
        beta_5 = 0.0
        beta_6 = 0.0
        lambda_1 = 0.08
        lambda_2 = 0.0
        lambda_3 = 0.0
        lambda_4 = 0.0
        lambda_5 = 0.0
        lambda_6 = 0.0
    []
[]

[BCs]
    [right_group1]
        type = DirichletBC
        variable = flux_group1
        boundary = 'right'
        value = 0
    []

    [right_group2]
        type = DirichletBC
        variable = flux_group2
        boundary = 'right'
        value = 0
    []

    [right_c1]
        type = DirichletBC
        variable = delayed_c1
        boundary = 'right'
        value = 0
    []

    [top_group1]
        type = DirichletBC
        variable = flux_group1
        boundary = 'top'
        value = 0
    []

    [top_group2]
        type = DirichletBC
        variable = flux_group2
        boundary = 'top'
        value = 0
    []

    [top_c1]
        type = DirichletBC
        variable = delayed_c1
        boundary = 'top'
        value = 0
    []
[]

[ICs]
    [ic_flux1]
        type = SolutionIC
        solution_uo = eigensolution
        variable = flux_group1
        from_variable = 'flux_group1'
        block = '1 2 3'
    []

    [ic_flux2]
        type = SolutionIC
        solution_uo = eigensolution
        variable = flux_group2
        from_variable = 'flux_group2'
        block = '1 2 3'
    []

    [ic_c1]
        type = SolutionIC
        solution_uo = eigensolution
        variable = delayed_c1
        from_variable = 'delayed_c1'
        block = '1 2 3'
    []
[]

[UserObjects]
    [eigensolution]
        type = SolutionUserObject
        mesh = 'results/Eigen_80*80/TWIGL_Twogroups_Eigenproblem_out.e'
        system_variables = 'flux_group1 flux_group2 delayed_c1'
        timestep = LATEST
    []
[]

[Executioner]
  type = Transient
  solve_type = 'PJFNK'
  num_steps = 50
  dt = 0.01
[]

[Postprocessors]
  [fnorm]
    type = ElementIntegralVariablePostprocessor
    variable = fission
    execute_on = 'initial timestep_end'
  []
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]