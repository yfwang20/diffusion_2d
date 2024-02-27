[Mesh]
    # TODO
[]

[Variables]
    [flux]
        order = FIRST
        family = LAGRANGE
    []
[]

[Kernels]
    [absorption]
        type = Absorption
        variable = flux
    []

    [diffusion]
        type = Diffusion_term
        variable = flux
    []

    [fission]
        type = Fission
        variable = flux
        extra_vector_tags = 'eigen'
    []
[]

[Materials]
    [materail_1]
        type = Material_1
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.08
        fission_cross_section_v = 0.01035
    []

    [materail_2]
        type = Material_2
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.08
        fission_cross_section_v = 0.01035
    []

    [materail_3]
        type = Material_3
        diffusion_coefficient = 0.9
        absorption_cross_section = 0.029
        fission_cross_section_v = 0.00315
    []
[]

[BCs]
    #TODO
[]

[Executioner]
    type = Eigenvalue
[]

[Outputs]
  execute_on = 'timestep_end'
  exodus = true
  csv = true
[]