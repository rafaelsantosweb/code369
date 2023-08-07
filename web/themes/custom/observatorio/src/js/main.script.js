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
