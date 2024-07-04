[Mesh]
  [generator]
    type = GeneratedMeshGenerator
    dim = 2
    xmax = 80
    ymax = 80
    nx = 100
    ny = 100
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

[Preconditioning]
  active = pbp_test
  [bdp]
      type = SMP
      petsc_options_iname = '-pc_type'
      petsc_options_value = 'lu'
  []
  
  [smp_test]
      type = SMP
      #full = true
      off_diag_row    = 'flux_two'
      off_diag_column = 'flux_one'
      petsc_options_iname = '-pc_type'
      petsc_options_value = 'ilu'
  []


  [smp_all]
      type = SMP
      full = true
      # off_diag_row    = 'flux_one flux_two delayed_c1 delayed_c1 flux_one flux_two'
      # off_diag_column = 'flux_two flux_one flux_one flux_two delayed_c1 delayed_c1'
      petsc_options_iname = '-pc_type'
      petsc_options_value = 'lu'
  []

  [smp_lt]
      type = SMP
      #full = true
      off_diag_row    = 'flux_two delayed_c1 delayed_c1'
      off_diag_column = 'flux_one flux_one flux_two'
      petsc_options_iname = '-pc_type'
      petsc_options_value = 'lu'
  []

  [pbp]
    type = PBP
    solve_order = 'flux_one flux_two delayed_c1'
    preconditioner  = 'LU LU LU'
    #full = true
    off_diag_row    = 'flux_two delayed_c1'
    off_diag_column = 'flux_one flux_two'
  []

	[pbp_lt]
		type = PBP
		solve_order = 'flux_one flux_two delayed_c1'
		preconditioner  = 'LU LU LU'
		#full = true
		off_diag_row    = 'flux_two delayed_c1 delayed_c1'
		off_diag_column = 'flux_one flux_two flux_one'
  []

  [pbp_test]
		type = PBP
		solve_order = 'flux_one flux_two delayed_c1'
		preconditioner  = 'iLU iLU iLU'
		#full = true
		off_diag_row    = 'flux_two'
		off_diag_column = 'flux_one'
  []

  [pbp_all]
		type = PBP
		solve_order = 'flux_one flux_two delayed_c1'
		preconditioner  = 'LU LU LU'
		#full = true
		off_diag_row    = 'flux_one flux_two delayed_c1 delayed_c1 flux_one flux_two'
		off_diag_column = 'flux_two flux_one flux_one flux_two delayed_c1 delayed_c1'
  []
[]



[Variables]
    [flux_one]
        order = FIRST
        family = LAGRANGE
    []

    [flux_two]
        order = FIRST
        family = LAGRANGE
    []

    [delayed_c1]
        order = FIRST
        family = LAGRANGE
    []
[]

[AuxVariables]
    [fission]
        order = CONSTANT
        family = MONOMIAL
    []
[]

[Kernels]
    [diffusion_group1]
      type = Diffusion_term_Twogroups_group1
      variable = flux_one
    []

    [absorption_group1]
        type = Absorption_Twogroups_group1
        variable = flux_one
    []

    [scattering_group1]
      type = Scattering_Twogroups_group1
      variable = flux_one
      otherflux_1 = flux_two
    []

    [fission_group1]
        type = Fission_Twogroups_Eigenproblem_group1
        variable = flux_one
        otherflux_1 = flux_two
        extra_vector_tags = 'eigen'
        coefficient = -1.0
    []


    [diffusion_group2]
      type = Diffusion_term_Twogroups_group2
      variable = flux_two
    []

    [absorption_group2]
        type = Absorption_Twogroups_group2
        variable = flux_two
    []

    [scattering_group2]
      type = Scattering_Twogroups_group2
      variable = flux_two
      otherflux_1 = flux_one
    []

    [fission_group2]
        type = Fission_Twogroups_Eigenproblem_group2
        variable = flux_two
        otherflux_1 = flux_one
        extra_vector_tags = 'eigen'
        coefficient = -1.0
    []


    [delayed_nucleus_c1_decay]
        type = DelayedNeutron_Decay
        variable = delayed_c1
        num = 1
    []

    [delayed_nucleus_c1_fission]
        type = DelayedNeutron_Fission
        variable = delayed_c1
        num = 1
        coefficient = -1.0
        flux_group1 = flux_one
        flux_group2 = flux_two
        extra_vector_tags = 'eigen'
    []
[]

[AuxKernels]
    [fission_aux]
        type = Fission_aux
        variable = fission
        flux_group1 = flux_one
        flux_group2 = flux_two
        execute_on = 'initial linear'
    []
[]

[Materials]
    [materail_1]
        type = Material_TWIGL_Twogroups
        block = '1'
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
        variable = flux_one
        boundary = 'right'
        value = 0
    []

    [right_group2]
        type = DirichletBC
        variable = flux_two
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
        variable = flux_one
        boundary = 'top'
        value = 0
    []

    [top_group2]
        type = DirichletBC
        variable = flux_two
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

[Executioner]
    type = Eigenvalue
    #solve_type = PJFNK
    solve_type = JFNK
    #l_tol = 0.001
    #l_abs_tol = 1e-50
    #nl_abs_tol = 1e-50
    #auto_preconditioning=false
    #output_after_power_iterations = false
	  free_power_iterations = 0
    normal_factor = 1
    normalization = max_flux_1
[]

[Postprocessors]
  [fnorm]
    type = ElementIntegralVariablePostprocessor
    variable = fission
    execute_on = 'initial linear'
  []

  [max_flux_1]
        type = ElementExtremeValue
        variable = flux_one
        execute_on = 'linear'
    []
[]

[VectorPostprocessors]
  [eigenvalues]
    type = Eigenvalues
    execute_on = 'timestep_end'
  []

  [diagonal_flux]
    type = PointValueSampler
    variable = 'flux_one flux_two'
    points = '0 0 0 1 1 0 2 2 0 3 3 0 4 4 0 5 5 0 6 6 0 7 7 0 8 8 0 9 9 0 10 10 0 11 11 0 12 12 0 13 13 0 14 14 0 15 15 0 16 16 0 17 17 0 18 18 0 19 19 0 20 20 0 21 21 0 22 22 0 23 23 0 24 24 0 25 25 0 26 26 0 27 27 0 28 28 0 29 29 0 30 30 0 31 31 0 32 32 0 33 33 0 34 34 0 35 35 0 36 36 0 37 37 0 38 38 0 39 39 0 40 40 0 41 41 0 42 42 0 43 43 0 44 44 0 45 45 0 46 46 0 47 47 0 48 48 0 49 49 0 50 50 0 51 51 0 52 52 0 53 53 0 54 54 0 55 55 0 56 56 0 57 57 0 58 58 0 59 59 0 60 60 0 61 61 0 62 62 0 63 63 0 64 64 0 65 65 0 66 66 0 67 67 0 68 68 0 69 69 0 70 70 0 71 71 0 72 72 0 73 73 0 74 74 0 75 75 0 76 76 0 77 77 0 78 78 0 79 79 0 80 80 0'
    sort_by = x
  []
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]