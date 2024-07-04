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

[Variables]
    [flux]
        order = FIRST
        family = LAGRANGE
    []
[]


[Kernels]
    [absorption]
        type = Absorption_Singlegroup
        variable = flux
    []

    [diffusion]
        type = Diffusion_term_Singlegroup
        variable = flux
    []

    [fission]
        type = Fission_Singlegroup
        variable = flux
        extra_vector_tags = 'eigen'
        coefficient = -1.0
    []
[]

[Materials]
    [materail_1]
        type = Material_TWIGL_Singlegroup
        block = '1'
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.08
        fission_cross_section_v = 0.1035
    []

    [materail_2]
        type = Material_TWIGL_Singlegroup
        block = '2'
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.08
        fission_cross_section_v = 0.1035
    []

    [materail_3]
        type = Material_TWIGL_Singlegroup
        block = '3'
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.029
        fission_cross_section_v = 0.0315
    []
[]

[BCs]
    [right]
        type = DirichletBC
        variable = flux
        boundary = 'right'
        value = 0
    []

    [top]
        type = DirichletBC
        variable = flux
        boundary = 'top'
        value = 0
    []
[]

[Executioner]
    type = Eigenvalue
    normal_factor = 1
    normalization = max_flux
[]

[VectorPostprocessors]
  [eigenvalues]
    type = Eigenvalues
    execute_on = 'timestep_end'
  []

  [diagonal_flux]
    type = PointValueSampler
    variable = 'flux'
    points = '0 0 0 1 1 0 2 2 0 3 3 0 4 4 0 5 5 0 6 6 0 7 7 0 8 8 0 9 9 0 10 10 0 11 11 0 12 12 0 13 13 0 14 14 0 15 15 0 16 16 0 17 17 0 18 18 0 19 19 0 20 20 0 21 21 0 22 22 0 23 23 0 24 24 0 25 25 0 26 26 0 27 27 0 28 28 0 29 29 0 30 30 0 31 31 0 32 32 0 33 33 0 34 34 0 35 35 0 36 36 0 37 37 0 38 38 0 39 39 0 40 40 0 41 41 0 42 42 0 43 43 0 44 44 0 45 45 0 46 46 0 47 47 0 48 48 0 49 49 0 50 50 0 51 51 0 52 52 0 53 53 0 54 54 0 55 55 0 56 56 0 57 57 0 58 58 0 59 59 0 60 60 0 61 61 0 62 62 0 63 63 0 64 64 0 65 65 0 66 66 0 67 67 0 68 68 0 69 69 0 70 70 0 71 71 0 72 72 0 73 73 0 74 74 0 75 75 0 76 76 0 77 77 0 78 78 0 79 79 0 80 80 0'
    sort_by = x
  []
[]

[Postprocessors]
    [max_flux]
        type = ElementExtremeValue
        variable = flux
        execute_on = 'linear'
    []
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]