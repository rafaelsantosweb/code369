import { Toast, Tooltip } from './_bootstrap';

( function () {
	// * Tooltip initialization, remove it if not necessary
	document
		.querySelectorAll( '[data-toggle="tooltip"]' )
		.forEach( ( tooltipElement ) => new Tooltip( tooltipElement ) );

	// * Toast initialization, remove it if not necessary
	document
		.querySelectorAll( '.toast' )
		.forEach( ( toastElement ) => new Toast( toastElement ) );

} )();

// jquery block
( function ( $ ) {
	let log = console.log.bind( console );

	// show the modal when clicking the button
	$( '.authenticated-modal a' ).on( 'click', function ( e ) {
		e.stopPropagation();
		// $( this ).find( '[autofocus]' ).focus();
		$( '#authenticatedModal' ).modal( 'show' );
		return false;
	} );

	// closes the modal
	$( '.modal button' ).on( 'hidden.bs.modal click', function ( e ) {
		$( '.modal' ).modal( 'hide' );
	} );
} )( jQuery );


// jquery block
( function ( $ ) {


  const $headerMobileToggleContainer = document.createElement('div');
  const $headerMobileToggle = document.createElement('div');
  $($headerMobileToggleContainer).addClass('header-mobile-toggle-container');
  $($headerMobileToggle).addClass('header-mobile-toggle');
	$($headerMobileToggleContainer).append($headerMobileToggle);
	$('header.page__header').append($headerMobileToggleContainer);

  $($headerMobileToggleContainer).on('click', function(e) {
    $('body').toggleClass('header-mobile-open');
  });

  $('header ul.nav').append(`<li class="nav-item show-mobile search-button">
  <a href="/search/node" class="nav-link" data-drupal-link-system-path="/search/node">Buscar</a>
</li>`);
} )( jQuery );


//função para mover os botões da pagina de estudo para outra div
( function ($){
	if($('body').hasClass('node-type--estudos')){
		document.addEventListener('DOMContentLoaded', function() {
			
			var newParent = document.querySelector('.estudos-internas .col:nth-child(2)');
			
			try {
				var childToMove2 = $('.paragraph_attachments');
				var botao_anexo = $('.button-attachments-estudos').find('a');
				
				botao_anexo.attr('target', '_blank');
				childToMove2.appendTo(newParent);
			} catch (error) {
			}
			
			try {
				var childToMove = $('.paragraph_cta');
				var botao_link_externo = $('.button-acessar-estudo').find('a');

				botao_link_externo.attr('target', '_blank');
				childToMove.appendTo(newParent);
			} catch (error) {
			}
			
		})
	}
} )( jQuery );


//função nav tab

(function ($) {
	document.addEventListener('DOMContentLoaded', ()=>{
		var texto_titulo = $('.page-title').text().replace(/\s+/g, ' ').trim();

		$('.tabs-cloud .field-content > a:nth-child(2)').filter(function(){
			return $(this).text().replace(/\s+/g, ' ').trim() === texto_titulo;
		}).addClass('is_active');

	})
}) (jQuery);

//Função para mover o bloco div do form de busca para o bloco de navegação principal

( function ($){
	
	$(function() {
		
		const header = $('header > .header_container > .block--navegacaoprincipal');
		
		try {
			const childToMove = $('header > .header_container > .block--formulariodebusca');
			childToMove.appendTo(header);

		} catch (error) {
			console.log("Não foi encontrado a div Filho ")
		}

		const iconBusca = header.find('#icon-busca');
		const formBarraBusca = header.find('.block--formulariodebusca');
		const inputBarraBusca = formBarraBusca.find('form > .form-item > input');

		function toggleBarraBusca() {
			formBarraBusca.slideToggle(200);
			iconBusca.toggleClass('mostrando');
			inputBarraBusca.val('');
		}

		iconBusca.on('click', function () {
			toggleBarraBusca();
		});
		

		$(document).on('click', function(event) {
			// Verifica se o clique foi fora da div
			if (!$(event.target).closest(formBarraBusca).length && !$(event.target).is(iconBusca) && (formBarraBusca.css('display') === 'block')) {
				toggleBarraBusca();
			}
		});

	})
	
} )( jQuery );
