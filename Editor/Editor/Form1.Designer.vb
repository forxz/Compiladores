﻿<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form reemplaza a Dispose para limpiar la lista de componentes.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requerido por el Diseñador de Windows Forms
    Private components As System.ComponentModel.IContainer

    'NOTA: el Diseñador de Windows Forms necesita el siguiente procedimiento
    'Se puede modificar usando el Diseñador de Windows Forms.  
    'No lo modifique con el editor de código.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip()
        Me.ArchivoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.AbrirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NuevoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.GuardarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SalirToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.EdicionToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.DeshacerToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.RehacerToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CortarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CopiarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.PegarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.SeleccionarTodoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.LimpiarTexoToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.CompilarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ScannerToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ScannerParserToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.NuevaVentanaToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.LeemeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ParametrosToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.ToolStrip1 = New System.Windows.Forms.ToolStrip()
        Me.NuevoDoc = New System.Windows.Forms.ToolStripButton()
        Me.AbrirDoc = New System.Windows.Forms.ToolStripButton()
        Me.btnGuardar = New System.Windows.Forms.ToolStripButton()
        Me.GuardarDoc = New System.Windows.Forms.ToolStripButton()
        Me.CopiarTexto = New System.Windows.Forms.ToolStripButton()
        Me.CortarTexto = New System.Windows.Forms.ToolStripButton()
        Me.PegarTexto = New System.Windows.Forms.ToolStripButton()
        Me.Undo = New System.Windows.Forms.ToolStripButton()
        Me.Redo = New System.Windows.Forms.ToolStripButton()
        Me.Fuente = New System.Windows.Forms.ToolStripButton()
        Me.ColorFondo = New System.Windows.Forms.ToolStripButton()
        Me.RichTextBox1 = New System.Windows.Forms.RichTextBox()
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.DataGridView1 = New System.Windows.Forms.DataGridView()
        Me.Codigo = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Descripcion = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Linea = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.Columna = New System.Windows.Forms.DataGridViewTextBoxColumn()
        Me.EjecutarToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem()
        Me.MenuStrip1.SuspendLayout()
        Me.ToolStrip1.SuspendLayout()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.DataGridView1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ArchivoToolStripMenuItem, Me.EdicionToolStripMenuItem, Me.CompilarToolStripMenuItem, Me.NuevaVentanaToolStripMenuItem, Me.ParametrosToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(916, 24)
        Me.MenuStrip1.TabIndex = 0
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'ArchivoToolStripMenuItem
        '
        Me.ArchivoToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.AbrirToolStripMenuItem, Me.NuevoToolStripMenuItem, Me.GuardarToolStripMenuItem, Me.SalirToolStripMenuItem})
        Me.ArchivoToolStripMenuItem.Name = "ArchivoToolStripMenuItem"
        Me.ArchivoToolStripMenuItem.Size = New System.Drawing.Size(60, 20)
        Me.ArchivoToolStripMenuItem.Text = "Archivo"
        '
        'AbrirToolStripMenuItem
        '
        Me.AbrirToolStripMenuItem.Name = "AbrirToolStripMenuItem"
        Me.AbrirToolStripMenuItem.Size = New System.Drawing.Size(116, 22)
        Me.AbrirToolStripMenuItem.Text = "Abrir"
        '
        'NuevoToolStripMenuItem
        '
        Me.NuevoToolStripMenuItem.Name = "NuevoToolStripMenuItem"
        Me.NuevoToolStripMenuItem.Size = New System.Drawing.Size(116, 22)
        Me.NuevoToolStripMenuItem.Text = "Nuevo"
        '
        'GuardarToolStripMenuItem
        '
        Me.GuardarToolStripMenuItem.Name = "GuardarToolStripMenuItem"
        Me.GuardarToolStripMenuItem.Size = New System.Drawing.Size(116, 22)
        Me.GuardarToolStripMenuItem.Text = "Guardar"
        '
        'SalirToolStripMenuItem
        '
        Me.SalirToolStripMenuItem.Name = "SalirToolStripMenuItem"
        Me.SalirToolStripMenuItem.Size = New System.Drawing.Size(116, 22)
        Me.SalirToolStripMenuItem.Text = "Salir"
        '
        'EdicionToolStripMenuItem
        '
        Me.EdicionToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.DeshacerToolStripMenuItem, Me.RehacerToolStripMenuItem, Me.CortarToolStripMenuItem, Me.CopiarToolStripMenuItem, Me.PegarToolStripMenuItem, Me.SeleccionarTodoToolStripMenuItem, Me.LimpiarTexoToolStripMenuItem})
        Me.EdicionToolStripMenuItem.Name = "EdicionToolStripMenuItem"
        Me.EdicionToolStripMenuItem.Size = New System.Drawing.Size(58, 20)
        Me.EdicionToolStripMenuItem.Text = "Edición"
        '
        'DeshacerToolStripMenuItem
        '
        Me.DeshacerToolStripMenuItem.Name = "DeshacerToolStripMenuItem"
        Me.DeshacerToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.DeshacerToolStripMenuItem.Text = "Deshacer"
        '
        'RehacerToolStripMenuItem
        '
        Me.RehacerToolStripMenuItem.Name = "RehacerToolStripMenuItem"
        Me.RehacerToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.RehacerToolStripMenuItem.Text = "Rehacer"
        '
        'CortarToolStripMenuItem
        '
        Me.CortarToolStripMenuItem.Name = "CortarToolStripMenuItem"
        Me.CortarToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.CortarToolStripMenuItem.Text = "Cortar"
        '
        'CopiarToolStripMenuItem
        '
        Me.CopiarToolStripMenuItem.Name = "CopiarToolStripMenuItem"
        Me.CopiarToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.CopiarToolStripMenuItem.Text = "Copiar"
        '
        'PegarToolStripMenuItem
        '
        Me.PegarToolStripMenuItem.Name = "PegarToolStripMenuItem"
        Me.PegarToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.PegarToolStripMenuItem.Text = "Pegar"
        '
        'SeleccionarTodoToolStripMenuItem
        '
        Me.SeleccionarTodoToolStripMenuItem.Name = "SeleccionarTodoToolStripMenuItem"
        Me.SeleccionarTodoToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.SeleccionarTodoToolStripMenuItem.Text = "Seleccionar todo"
        '
        'LimpiarTexoToolStripMenuItem
        '
        Me.LimpiarTexoToolStripMenuItem.Name = "LimpiarTexoToolStripMenuItem"
        Me.LimpiarTexoToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.LimpiarTexoToolStripMenuItem.Text = "Limpiar texo"
        '
        'CompilarToolStripMenuItem
        '
        Me.CompilarToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ScannerToolStripMenuItem, Me.ScannerParserToolStripMenuItem, Me.EjecutarToolStripMenuItem})
        Me.CompilarToolStripMenuItem.Name = "CompilarToolStripMenuItem"
        Me.CompilarToolStripMenuItem.Size = New System.Drawing.Size(68, 20)
        Me.CompilarToolStripMenuItem.Text = "Compilar"
        '
        'ScannerToolStripMenuItem
        '
        Me.ScannerToolStripMenuItem.Name = "ScannerToolStripMenuItem"
        Me.ScannerToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.ScannerToolStripMenuItem.Text = "Scanner"
        '
        'ScannerParserToolStripMenuItem
        '
        Me.ScannerParserToolStripMenuItem.Name = "ScannerParserToolStripMenuItem"
        Me.ScannerParserToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.ScannerParserToolStripMenuItem.Text = "Parser"
        '
        'NuevaVentanaToolStripMenuItem
        '
        Me.NuevaVentanaToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.LeemeToolStripMenuItem})
        Me.NuevaVentanaToolStripMenuItem.Name = "NuevaVentanaToolStripMenuItem"
        Me.NuevaVentanaToolStripMenuItem.Size = New System.Drawing.Size(53, 20)
        Me.NuevaVentanaToolStripMenuItem.Text = "Ayuda"
        '
        'LeemeToolStripMenuItem
        '
        Me.LeemeToolStripMenuItem.Name = "LeemeToolStripMenuItem"
        Me.LeemeToolStripMenuItem.Size = New System.Drawing.Size(109, 22)
        Me.LeemeToolStripMenuItem.Text = "Léeme"
        '
        'ParametrosToolStripMenuItem
        '
        Me.ParametrosToolStripMenuItem.Name = "ParametrosToolStripMenuItem"
        Me.ParametrosToolStripMenuItem.Size = New System.Drawing.Size(79, 20)
        Me.ParametrosToolStripMenuItem.Text = "Parámetros"
        '
        'ToolStrip1
        '
        Me.ToolStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.NuevoDoc, Me.AbrirDoc, Me.btnGuardar, Me.GuardarDoc, Me.CopiarTexto, Me.CortarTexto, Me.PegarTexto, Me.Undo, Me.Redo, Me.Fuente, Me.ColorFondo})
        Me.ToolStrip1.Location = New System.Drawing.Point(0, 24)
        Me.ToolStrip1.Name = "ToolStrip1"
        Me.ToolStrip1.Size = New System.Drawing.Size(916, 25)
        Me.ToolStrip1.TabIndex = 1
        Me.ToolStrip1.Text = "ToolStrip1"
        '
        'NuevoDoc
        '
        Me.NuevoDoc.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.NuevoDoc.Image = CType(resources.GetObject("NuevoDoc.Image"), System.Drawing.Image)
        Me.NuevoDoc.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.NuevoDoc.Name = "NuevoDoc"
        Me.NuevoDoc.Size = New System.Drawing.Size(23, 22)
        Me.NuevoDoc.Text = "Nuevo Archivo"
        '
        'AbrirDoc
        '
        Me.AbrirDoc.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.AbrirDoc.Image = CType(resources.GetObject("AbrirDoc.Image"), System.Drawing.Image)
        Me.AbrirDoc.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.AbrirDoc.Name = "AbrirDoc"
        Me.AbrirDoc.Size = New System.Drawing.Size(23, 22)
        Me.AbrirDoc.Text = "Abrir"
        '
        'btnGuardar
        '
        Me.btnGuardar.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.btnGuardar.Image = CType(resources.GetObject("btnGuardar.Image"), System.Drawing.Image)
        Me.btnGuardar.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.btnGuardar.Name = "btnGuardar"
        Me.btnGuardar.Size = New System.Drawing.Size(23, 22)
        Me.btnGuardar.Text = "Guardar"
        '
        'GuardarDoc
        '
        Me.GuardarDoc.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.GuardarDoc.Image = CType(resources.GetObject("GuardarDoc.Image"), System.Drawing.Image)
        Me.GuardarDoc.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.GuardarDoc.Name = "GuardarDoc"
        Me.GuardarDoc.Size = New System.Drawing.Size(23, 22)
        Me.GuardarDoc.Text = "Guardar Como"
        '
        'CopiarTexto
        '
        Me.CopiarTexto.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.CopiarTexto.Image = CType(resources.GetObject("CopiarTexto.Image"), System.Drawing.Image)
        Me.CopiarTexto.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.CopiarTexto.Name = "CopiarTexto"
        Me.CopiarTexto.Size = New System.Drawing.Size(23, 22)
        Me.CopiarTexto.Text = "Copiar"
        '
        'CortarTexto
        '
        Me.CortarTexto.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.CortarTexto.Image = CType(resources.GetObject("CortarTexto.Image"), System.Drawing.Image)
        Me.CortarTexto.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.CortarTexto.Name = "CortarTexto"
        Me.CortarTexto.Size = New System.Drawing.Size(23, 22)
        Me.CortarTexto.Text = "Cortar"
        '
        'PegarTexto
        '
        Me.PegarTexto.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.PegarTexto.Image = CType(resources.GetObject("PegarTexto.Image"), System.Drawing.Image)
        Me.PegarTexto.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.PegarTexto.Name = "PegarTexto"
        Me.PegarTexto.Size = New System.Drawing.Size(23, 22)
        Me.PegarTexto.Text = "Pegar"
        '
        'Undo
        '
        Me.Undo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.Undo.Image = CType(resources.GetObject("Undo.Image"), System.Drawing.Image)
        Me.Undo.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.Undo.Name = "Undo"
        Me.Undo.Size = New System.Drawing.Size(23, 22)
        Me.Undo.Text = "Deshacer"
        '
        'Redo
        '
        Me.Redo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.Redo.Image = CType(resources.GetObject("Redo.Image"), System.Drawing.Image)
        Me.Redo.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.Redo.Name = "Redo"
        Me.Redo.Size = New System.Drawing.Size(23, 22)
        Me.Redo.Text = "Rehacer"
        '
        'Fuente
        '
        Me.Fuente.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.Fuente.Image = CType(resources.GetObject("Fuente.Image"), System.Drawing.Image)
        Me.Fuente.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.Fuente.Name = "Fuente"
        Me.Fuente.Size = New System.Drawing.Size(23, 22)
        Me.Fuente.Text = "Fuente"
        '
        'ColorFondo
        '
        Me.ColorFondo.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image
        Me.ColorFondo.Image = CType(resources.GetObject("ColorFondo.Image"), System.Drawing.Image)
        Me.ColorFondo.ImageTransparentColor = System.Drawing.Color.Magenta
        Me.ColorFondo.Name = "ColorFondo"
        Me.ColorFondo.Size = New System.Drawing.Size(23, 22)
        Me.ColorFondo.Text = "Color de fondo"
        '
        'RichTextBox1
        '
        Me.RichTextBox1.AcceptsTab = True
        Me.RichTextBox1.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.RichTextBox1.Font = New System.Drawing.Font("Microsoft Sans Serif", 14.25!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.RichTextBox1.Location = New System.Drawing.Point(39, 54)
        Me.RichTextBox1.Margin = New System.Windows.Forms.Padding(30)
        Me.RichTextBox1.Name = "RichTextBox1"
        Me.RichTextBox1.ShortcutsEnabled = False
        Me.RichTextBox1.Size = New System.Drawing.Size(867, 458)
        Me.RichTextBox1.TabIndex = 2
        Me.RichTextBox1.Text = ""
        '
        'PictureBox1
        '
        Me.PictureBox1.Anchor = CType(((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left), System.Windows.Forms.AnchorStyles)
        Me.PictureBox1.BackColor = System.Drawing.SystemColors.ActiveBorder
        Me.PictureBox1.Location = New System.Drawing.Point(0, 57)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(39, 455)
        Me.PictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize
        Me.PictureBox1.TabIndex = 3
        Me.PictureBox1.TabStop = False
        '
        'Timer1
        '
        '
        'DataGridView1
        '
        Me.DataGridView1.AllowUserToOrderColumns = True
        Me.DataGridView1.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill
        Me.DataGridView1.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllHeaders
        Me.DataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize
        Me.DataGridView1.Columns.AddRange(New System.Windows.Forms.DataGridViewColumn() {Me.Codigo, Me.Descripcion, Me.Linea, Me.Columna})
        Me.DataGridView1.Dock = System.Windows.Forms.DockStyle.Bottom
        Me.DataGridView1.Location = New System.Drawing.Point(0, 371)
        Me.DataGridView1.Name = "DataGridView1"
        Me.DataGridView1.Size = New System.Drawing.Size(916, 150)
        Me.DataGridView1.TabIndex = 4
        '
        'Codigo
        '
        Me.Codigo.HeaderText = "Codigo"
        Me.Codigo.Name = "Codigo"
        '
        'Descripcion
        '
        Me.Descripcion.HeaderText = "Descripcion"
        Me.Descripcion.Name = "Descripcion"
        '
        'Linea
        '
        Me.Linea.HeaderText = "Linea"
        Me.Linea.Name = "Linea"
        '
        'Columna
        '
        Me.Columna.HeaderText = "Columna"
        Me.Columna.Name = "Columna"
        '
        'EjecutarToolStripMenuItem
        '
        Me.EjecutarToolStripMenuItem.Name = "EjecutarToolStripMenuItem"
        Me.EjecutarToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.EjecutarToolStripMenuItem.Text = "Ejecutar"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.AutoScroll = True
        Me.ClientSize = New System.Drawing.Size(916, 521)
        Me.Controls.Add(Me.DataGridView1)
        Me.Controls.Add(Me.PictureBox1)
        Me.Controls.Add(Me.RichTextBox1)
        Me.Controls.Add(Me.ToolStrip1)
        Me.Controls.Add(Me.MenuStrip1)
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "Form1"
        Me.Text = "Simplex Editor"
        Me.WindowState = System.Windows.Forms.FormWindowState.Maximized
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        Me.ToolStrip1.ResumeLayout(False)
        Me.ToolStrip1.PerformLayout()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.DataGridView1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout

End Sub
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents ArchivoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents AbrirToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents NuevoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents GuardarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SalirToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents EdicionToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents DeshacerToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RehacerToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CortarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CopiarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents PegarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SeleccionarTodoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents LimpiarTexoToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ToolStrip1 As System.Windows.Forms.ToolStrip
    Friend WithEvents NuevoDoc As System.Windows.Forms.ToolStripButton
    Friend WithEvents AbrirDoc As System.Windows.Forms.ToolStripButton
    Friend WithEvents GuardarDoc As System.Windows.Forms.ToolStripButton
    Friend WithEvents CortarTexto As System.Windows.Forms.ToolStripButton
    Friend WithEvents PegarTexto As System.Windows.Forms.ToolStripButton
    Friend WithEvents Undo As System.Windows.Forms.ToolStripButton
    Friend WithEvents Redo As System.Windows.Forms.ToolStripButton
    Friend WithEvents Fuente As System.Windows.Forms.ToolStripButton
    Friend WithEvents ColorFondo As System.Windows.Forms.ToolStripButton
    Friend WithEvents NuevaVentanaToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents LeemeToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RichTextBox1 As System.Windows.Forms.RichTextBox
    Friend WithEvents btnGuardar As System.Windows.Forms.ToolStripButton
    Friend WithEvents CompilarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ScannerToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ParametrosToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CopiarTexto As System.Windows.Forms.ToolStripButton
    Friend WithEvents PictureBox1 As System.Windows.Forms.PictureBox
    Friend WithEvents Timer1 As System.Windows.Forms.Timer
    Friend WithEvents ScannerParserToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents DataGridView1 As System.Windows.Forms.DataGridView
    Friend WithEvents Codigo As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents Descripcion As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents Linea As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents Columna As System.Windows.Forms.DataGridViewTextBoxColumn
    Friend WithEvents EjecutarToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem

End Class
