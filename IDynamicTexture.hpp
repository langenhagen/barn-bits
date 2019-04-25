/**
 * This file provides an abstract superclass for Dynamic Textures for OGRE
 * @author barn
 * @version 20130513
 */
#pragma once

///////////////////////////////////////////////////////////////////////////////
// INCLUDES project headers

///////////////////////////////////////////////////////////////////////////////
//INCLUDES C/C++ standard library (and other external libraries)
#include <OGRE/Ogre.h>

///////////////////////////////////////////////////////////////////////////////
// DEFINES and MACROS

///////////////////////////////////////////////////////////////////////////////
// NAMESPACE, CONSTANTS and TYPE DECLARATIONS/IMPLEMENTATIONS


namespace DynamicOgreTexture
{

	/**
	 * This class represents an abstract superclass for dynamic textures for OGRE.
	 * It is, in particular a FrameListener, that maps a dynamic texture
	 * onto some texture pointer. It is also viable as a Compositor listener.
	 */
	class IDynamicTexture :
		public Ogre::FrameListener /*frameRenderingQueued*/,
		public Ogre::CompositorInstance::Listener /*notifyMaterialRender, notifyMaterialSetup*/
	{
	protected: // vars

		/// The name of the texture within Ogre's resource pool.
		std::string _texture_name;

		/// The texture unit state to which the Texture shall be assigned.
		Ogre::TextureUnitState* _texture_unit_state;

		/**
		 * Specifies, if the texture shall be rendered with alpha or not.
		 * Be aware of it when overriding createDynamicTexture()!
		 */
		 bool _is_use_alpha;

	public: // constructor & destructor

		/**
		 * Constructor #1.
		 * @param texture_name The name of the texture. Should be unique..
		 * @param texture_unit_state The texture unit state on which the raw data
		 * shall be printed as a picture.
		 * @param is_use_alpha Specifies, whether to regard alpha channel of the dynamic texture.
		 */
		IDynamicTexture( std::string& texture_name, Ogre::TextureUnitState *texture_unit_state, bool is_use_alpha=false)
			: _texture_name( texture_name),
			_is_use_alpha( is_use_alpha),
			_texture_unit_state( texture_unit_state)
		{}

		/// Destructor.
		~IDynamicTexture()
		{}

	public: // methods

		/**
		 * Inherited from FrameListener.
		 */
		inline bool frameRenderingQueued( const Ogre::FrameEvent& evt)
		{
			_texture_unit_state->setTexture( createDynamicTexture());
			return true;
		}

		/**
		 * Inherited from CompositorInstance::Listener.
		 */
		void notifyMaterialSetup( Ogre::uint32 passId, Ogre::MaterialPtr &mat)
		{
			assert( mat->getBestTechnique()->getPass( passId)->getTextureUnitState("SecondTexture") != NULL);

			mat->getBestTechnique()->getPass( passId)->getTextureUnitState("SecondTexture")->setTexture( createDynamicTexture());
		}

		/**
		 * Inherited from CompositorInstance::Listener.
		 */
		void notifyMaterialRender(Ogre::uint32 passId, Ogre::MaterialPtr &mat)
		{
			mat->getBestTechnique()->getPass( passId)->getTextureUnitState("SecondTexture")->setTexture( createDynamicTexture());
		}

		inline void setUseAlpha( bool is_use_alpha)
		{
			_is_use_alpha = is_use_alpha;
		}

		/**
		 * Creates the dynamic texture.
		 * @return A texture pointer with the image of the texture memory.
		 */
		virtual Ogre::TexturePtr createDynamicTexture() = 0;

	}; // END class IDynamicTexture

} // END namespace DynamicOgreTexture
